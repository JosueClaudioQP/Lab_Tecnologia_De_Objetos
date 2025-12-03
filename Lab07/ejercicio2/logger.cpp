#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

enum NivelLog {
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    ofstream archivo;
    static Logger* instancia;
    NivelLog nivelMinimo;

    // Constructor privado
    Logger() : nivelMinimo(INFO) {
        archivo.open("bitacora.log", ios::app);
        if (!archivo.is_open()) {
            cerr << "Error: No se pudo abrir bitacora.log" << endl;
        }
    }

    // Obtener hora y fecha actual
    string obtenerTiempo() {
        time_t ahora = time(nullptr);
        string fecha = ctime(&ahora);
        fecha.pop_back(); // quitar salto de línea
        return fecha;
    }

    // Convertir enum → string
    string nivelToString(NivelLog n) {
        switch (n) {
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
        }
        return "INFO";
    }

public:
    // Deshabilitar copia
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    static Logger* getInstancia() {
        if (instancia == nullptr) {
            instancia = new Logger();
        }
        return instancia;
    }

    void setNivelMinimo(NivelLog nivel) {
        nivelMinimo = nivel;
    }

    // Log general
    void log(NivelLog nivel, const string& mensaje) {
        if (nivel < nivelMinimo) return;

        archivo << "[" << obtenerTiempo() << "] "
                << nivelToString(nivel)
                << " : " << mensaje << endl;
    }

    // Cerrar archivo (opcional)
    void cerrar() {
        if (archivo.is_open()) {
            archivo.close();
        }
    }
};

// Inicialización
Logger* Logger::instancia = nullptr;

int main() {
    Logger* logger = Logger::getInstancia();

    logger->setNivelMinimo(INFO);

    logger->log(INFO, "Inicio del sistema.");
    logger->log(WARNING, "Uso elevado de memoria detectado.");
    logger->log(ERROR, "No se pudo conectar al servidor.");

    // Módulo A
    logger->log(INFO, "[Modulo A] Cargando configuraciones...");

    // Módulo B
    logger->log(WARNING, "[Modulo B] Tiempo de respuesta lento.");

    // Simulación de error crítico
    logger->setNivelMinimo(WARNING); 
    logger->log(INFO, "Este mensaje no debe registrarse.");
    logger->log(ERROR, "Fallo critico en el módulo C");

    logger->cerrar();

    cout << "Se genero el log con multiples tipos de mensajes." << endl;

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

class ConexionBD {
private:
    static ConexionBD* instancia;
    bool conectado;
    string usuarioActual;
    int consultasEjecutadas;

    // Constructor privado
    ConexionBD() : conectado(false), usuarioActual(""), consultasEjecutadas(0) {}

public:
    // Deshabilitar copia
    ConexionBD(const ConexionBD&) = delete;
    void operator=(const ConexionBD&) = delete;

    static ConexionBD* getInstancia() {
        if (instancia == nullptr) {
            instancia = new ConexionBD();
        }
        return instancia;
    }

    // Conexión con usuario y contraseña
    void conectar(const string& usuario, const string& password) {
        if (conectado) {
            cout << "Ya existe una conexion activa por el usuario '" 
                 << usuarioActual << "'." << endl;
            return;
        }

        if (password == "12345") {  // clave simulada
            conectado = true;
            usuarioActual = usuario;
            cout << "Conexion establecida correctamente como '" 
                 << usuario << "'." << endl;
        } else {
            cout << "Error: contraseña incorrecta." << endl;
        }
    }

    void ejecutarConsulta(const string& q) {
        if (!conectado) {
            cout << "No hay conexion activa. No se puede ejecutar la consulta." << endl;
            return;
        }
        consultasEjecutadas++;
        cout << "Ejecutando consulta: " << q << endl;
    }

    void desconectar() {
        if (conectado) {
            cout << "Desconectando usuario '" << usuarioActual << "'..." << endl;
            conectado = false;
            usuarioActual = "";
        } else {
            cout << "No hay conexion activa para cerrar." << endl;
        }
    }

    void estado() {
        cout << "\nESTADO DE LA BD" << endl;
        cout << "Conexion: " << (conectado ? "Activa" : "Inactiva") << endl;
        if (conectado)
            cout << "Usuario: " << usuarioActual << endl;
        cout << "Consultas ejecutadas: " << consultasEjecutadas << endl;
    }
};

// Inicializar instancia
ConexionBD* ConexionBD::instancia = nullptr;

int main() {
    ConexionBD* bd1 = ConexionBD::getInstancia();
    ConexionBD* bd2 = ConexionBD::getInstancia();

    cout << "Intentando conectar con clave incorrecta..." << endl;
    bd1->conectar("admin", "0000");

    cout << "\nConectando con clave correcta..." << endl;
    bd1->conectar("admin", "12345");

    cout << "\nIntentando nueva conexion desde bd2..." << endl;
    bd2->conectar("usuario2", "12345");

    bd1->ejecutarConsulta("SELECT * FROM usuarios;");
    bd1->ejecutarConsulta("UPDATE productos SET precio = 50;");

    bd2->estado();

    cout << "\nDesconectando..." << endl;
    bd2->desconectar();

    bd1->estado();

    cout << "\n¿bd1 y bd2 son la misma instancia? "
         << ((bd1 == bd2) ? "Sí" : "No") << endl;

    return 0;
}

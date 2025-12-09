#ifndef CONTROL_JUEGO_H
#define CONTROL_JUEGO_H

#include <iostream>

class ControlJuego {
private:
    int nivel;
    int puntaje;
    int vidas;
    bool juegoActivo;

    // Constructor privado
    ControlJuego() : nivel(1), puntaje(0), vidas(3), juegoActivo(true) {}

    // Evitar copia
    ControlJuego(const ControlJuego&) = delete;
    ControlJuego& operator=(const ControlJuego&) = delete;

public:
    static ControlJuego& getInstance() {
        static ControlJuego instancia;
        return instancia;
    }

    // Gestión del estado
    void aumentarPuntaje(int p) { puntaje += p; }
    void perderVida() { vidas--; if (vidas <= 0) juegoActivo = false; }
    void avanzarNivel() { nivel++; }

    // Getters
    int getNivel() const { return nivel; }
    int getPuntaje() const { return puntaje; }
    int getVidas() const { return vidas; }
    bool getEstado() const { return juegoActivo; }

    void imprimirEstado() const {
        std::cout << "\n=== ESTADO DEL JUEGO ===\n";
        std::cout << "Nivel: " << nivel << "\n";
        std::cout << "Puntaje: " << puntaje << "\n";
        std::cout << "Vidas: " << vidas << "\n";
        std::cout << "Juego Activo: " << (juegoActivo ? "Sí" : "No") << "\n";
        std::cout << "=========================\n";
    }
};

#endif

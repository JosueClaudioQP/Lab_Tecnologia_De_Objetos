#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include "ControlJuego.h"

class Jugador {
public:
    void recogerMoneda() {
        ControlJuego::getInstance().aumentarPuntaje(10);
        std::cout << "[Jugador] Moneda recogida (+10).\n";
    }

    void completarNivel() {
        ControlJuego::getInstance().avanzarNivel();
        std::cout << "[Jugador] Nivel completado.\n";
    }
};

#endif

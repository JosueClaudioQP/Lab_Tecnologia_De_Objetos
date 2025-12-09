#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "ControlJuego.h"

class Interfaz {
public:
    void mostrar() {
        ControlJuego::getInstance().imprimirEstado();
    }
};

#endif

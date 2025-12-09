#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <iostream>
#include "ControlJuego.h"

class Enemigo {
public:
    void atacar() {
        ControlJuego::getInstance().perderVida();
        std::cout << "[Enemigo] Te ha atacado (-1 vida).\n";
    }
};

#endif

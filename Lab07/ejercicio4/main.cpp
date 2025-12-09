#include <iostream>
#include "Jugador.h"
#include "Enemigo.h"
#include "Interfaz.h"

int main() {
    Jugador jugador;
    Enemigo enemigo;
    Interfaz ui;

    ui.mostrar();

    jugador.recogerMoneda();
    jugador.recogerMoneda();
    enemigo.atacar();

    ui.mostrar();

    jugador.completarNivel();
    enemigo.atacar();
    enemigo.atacar(); // Podría terminar el juego

    ui.mostrar();

    return 0;
}

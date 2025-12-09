# Ejercicio 4: Control de Estado de Juego

## Descripción

Este ejercicio implementa un sistema de gestión de estado para un videojuego utilizando el patrón Singleton con la técnica Meyer's Singleton. Coordina el estado compartido entre múltiples componentes del juego (jugador, enemigos, interfaz) de manera desacoplada.

## Patrón de Diseño

**Meyer's Singleton (C++11)**

A diferencia de los ejercicios anteriores que usan punteros estáticos, este implementa el Singleton usando una variable estática local, que es thread-safe por diseño y no requiere gestión manual de memoria.

```cpp
static ControlJuego& getInstance() {
    static ControlJuego instancia;  // Variable estática local
    return instancia;                // Retorna por referencia
}
```

## Arquitectura del Sistema

### Estructura de Archivos

```
ejercicio4/
├── ControlJuego.h    # Singleton central con estado del juego
├── Jugador.h         # Acciones del jugador
├── Enemigo.h         # Acciones de enemigos
├── Interfaz.h        # Visualización del estado
└── main.cpp          # Orquestación de componentes
```

### Componentes

**ControlJuego** (Singleton)
- Gestiona el estado global del juego
- Almacena nivel, puntaje, vidas y estado activo
- Proporciona métodos para modificar el estado

**Jugador**
- Recoger monedas (aumenta puntaje)
- Completar niveles (avanza nivel)

**Enemigo**
- Atacar jugador (reduce vidas)
- Puede causar game over

**Interfaz**
- Muestra el estado actual del juego
- Accede al singleton para obtener información

## Estado del Juego

### Atributos

- `nivel`: Nivel actual del juego (inicial: 1)
- `puntaje`: Puntos acumulados (inicial: 0)
- `vidas`: Vidas restantes (inicial: 3)
- `juegoActivo`: Estado del juego (inicial: true)

### Métodos de Modificación

```cpp
void aumentarPuntaje(int p);  // Añade puntos
void perderVida();            // Reduce vidas, verifica game over
void avanzarNivel();          // Incrementa nivel
```

### Métodos de Consulta

```cpp
int getNivel() const;
int getPuntaje() const;
int getVidas() const;
bool getEstado() const;
void imprimirEstado() const;
```

## Compilación y Ejecución

```bash
g++ main.cpp -o juego
./juego
```

## Salida Esperada

```
=== ESTADO DEL JUEGO ===
Nivel: 1
Puntaje: 0
Vidas: 3
Juego Activo: Sí
=========================

[Jugador] Moneda recogida (+10).
[Jugador] Moneda recogida (+10).
[Enemigo] Te ha atacado (-1 vida).

=== ESTADO DEL JUEGO ===
Nivel: 1
Puntaje: 20
Vidas: 2
Juego Activo: Sí
=========================

[Jugador] Nivel completado.
[Enemigo] Te ha atacado (-1 vida).
[Enemigo] Te ha atacado (-1 vida).

=== ESTADO DEL JUEGO ===
Nivel: 2
Puntaje: 20
Vidas: 0
Juego Activo: No
=========================
```

## Flujo de Juego Simulado

### Estado Inicial
- Nivel 1, 0 puntos, 3 vidas, juego activo

### Secuencia de Eventos

1. Jugador recoge 2 monedas: +20 puntos
2. Enemigo ataca 1 vez: -1 vida (quedan 2)
3. Jugador completa nivel: nivel 2
4. Enemigo ataca 2 veces: -2 vidas (quedan 0)
5. Game Over automático (vidas <= 0)

## Ventajas de Meyer's Singleton

### Comparación con Singleton Clásico

| Característica | Singleton Clásico | Meyer's Singleton |
|----------------|-------------------|-------------------|
| Gestión memoria | Manual (new/delete) | Automática |
| Thread-safety | Requiere mutex | Nativo (C++11+) |
| Sintaxis | Puntero (*) | Referencia (&) |
| Inicialización | Explícita | Automática |
| Destrucción | Manual | Automática |

### Beneficios

- **Thread-Safe**: C++11 garantiza inicialización segura de variables estáticas locales
- **Sin Memory Leaks**: La destrucción es automática al finalizar el programa
- **Sintaxis Limpia**: No requiere verificación de nullptr
- **Más Simple**: Menos código que el patrón clásico

## Desacoplamiento de Componentes

Los componentes (Jugador, Enemigo, Interfaz) no se conocen entre sí. Solo interactúan a través del Singleton:

```cpp
// Jugador.h
void recogerMoneda() {
    ControlJuego::getInstance().aumentarPuntaje(10);
}

// Enemigo.h
void atacar() {
    ControlJuego::getInstance().perderVida();
}

// Interfaz.h
void mostrar() {
    ControlJuego::getInstance().imprimirEstado();
}
```

## Casos de Uso

Este patrón es ideal para:

- Gestión de estado en videojuegos
- Sistema de puntuación global
- Control de progresión de jugador
- Coordinación de múltiples sistemas de juego
- Persistencia de datos entre escenas
- HUD y sistemas de interfaz

## Ventajas

- Estado centralizado y consistente
- Componentes desacoplados
- Thread-safe por diseño
- Gestión automática de memoria
- Fácil acceso desde cualquier componente
- Previene inconsistencias de estado

## Limitaciones

- Estado global dificulta testing
- Acoplamiento implícito al Singleton
- Difícil implementar múltiples partidas simultáneas
- Complejidad para resetear el estado
- Puede violar el principio de responsabilidad única


## Mejores Prácticas Implementadas

- Headers con guardas de inclusión (#ifndef)
- Uso de const en métodos de consulta
- Separación de responsabilidades por archivo
- Nombres descriptivos de métodos
- Encapsulación de datos privados
- Destructor automático (RAII)

## Conclusión

Este ejercicio demuestra la implementación moderna del patrón Singleton utilizando Meyer's Singleton, que es preferible en C++11 y posteriores por su simplicidad, seguridad y gestión automática de recursos. La arquitectura modular permite extender fácilmente el juego con nuevos componentes sin modificar el código existente.
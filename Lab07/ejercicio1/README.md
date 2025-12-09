# Ejercicio 1: Sistema de Configuración Global

## Descripción

Este ejercicio implementa el patrón de diseño Singleton para gestionar la configuración global de una aplicación. Garantiza que todos los componentes del sistema accedan a la misma instancia de configuración, evitando inconsistencias.

## Patrón de Diseño

**Singleton Clásico con Puntero Estático**

El patrón Singleton asegura que una clase tenga una única instancia y proporciona un punto de acceso global a ella.

## Estructura del Código

### Componentes Principales

- **Constructor Privado**: Impide la creación directa de instancias
- **Instancia Estática**: Almacena la única instancia de la clase
- **Método getInstancia()**: Proporciona acceso controlado a la instancia
- **Prohibición de Copia**: Previene duplicación mediante copy constructor y operador de asignación

### Atributos de Configuración

- `idioma`: Lenguaje de la aplicación (por defecto: "ES")
- `zonaHoraria`: Zona horaria del sistema (por defecto: "GMT-5")

## Funcionalidades

### Métodos Públicos

- `getInstancia()`: Obtiene la única instancia de Configuracion
- `mostrar_configuracion()`: Muestra los valores actuales de configuración
- `setIdioma(string)`: Modifica el idioma de la aplicación
- `setZona(string)`: Modifica la zona horaria

## Compilación y Ejecución

```bash
g++ configuracion.cpp -o configuracion
./configuracion
```

## Salida Esperada

```
Configuracion desde c1:
Idioma: EN
Zona horaria: UTC

Configuracion desde c2 (misma instancia):
Idioma: EN
Zona horaria: UTC

¿c1 y c2 son el mismo objeto? Sí
```

## Demostración

El programa principal demuestra:

1. Obtención de la instancia desde dos punteros diferentes (c1 y c2)
2. Modificación de configuración a través de c1
3. Verificación de que c2 refleja los mismos cambios
4. Confirmación de que ambos punteros apuntan al mismo objeto

## Características del Patrón Implementado

**Inicialización Lazy**: La instancia se crea solo cuando se solicita por primera vez

**Thread-Safety**: Esta implementación NO es thread-safe. En aplicaciones multithreaded se requeriría sincronización adicional

**Gestión de Memoria**: Utiliza memoria dinámica sin liberación explícita (minor memory leak al finalizar)

## Casos de Uso

Este patrón es útil para:

- Configuraciones globales de aplicación
- Preferencias de usuario compartidas
- Parámetros de sistema centralizados
- Ajustes que deben ser consistentes en toda la aplicación

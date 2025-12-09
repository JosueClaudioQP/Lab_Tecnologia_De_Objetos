# Ejercicio 2: Sistema de Logging (Bitácora)

## Descripción

Este ejercicio implementa un sistema de logging centralizado utilizando el patrón Singleton. Permite registrar eventos del sistema en un archivo de bitácora con diferentes niveles de severidad y timestamps automáticos.

## Patrón de Diseño

**Singleton para Gestión de Recursos**

Garantiza que solo exista una instancia del logger, evitando múltiples archivos abiertos simultáneamente y asegurando que todos los módulos escriban en la misma bitácora.

## Estructura del Código

### Niveles de Log

```cpp
enum NivelLog {
    INFO,      // Información general
    WARNING,   // Advertencias
    ERROR      // Errores críticos
}
```

### Componentes Principales

- **Constructor Privado**: Abre el archivo `bitacora.log` en modo append
- **Instancia Estática**: Única instancia del logger
- **Nivel Mínimo**: Filtro configurable para mensajes
- **Timestamp Automático**: Marca temporal en cada entrada

## Funcionalidades

### Métodos Públicos

- `getInstancia()`: Obtiene la única instancia del logger
- `setNivelMinimo(NivelLog)`: Configura el nivel mínimo de registro
- `log(NivelLog, string)`: Registra un mensaje con nivel específico
- `cerrar()`: Cierra el archivo de bitácora

### Métodos Privados

- `obtenerTiempo()`: Genera timestamp en formato legible
- `nivelToString(NivelLog)`: Convierte enum a string

## Compilación y Ejecución

```bash
g++ logger.cpp -o logger
./logger
```

## Formato de Salida

Cada entrada en `bitacora.log` sigue el formato:

```
[Tue Dec  2 22:30:42 2025] NIVEL : Mensaje descriptivo
```

### Ejemplo de Log Generado

```
[Tue Dec  2 22:30:42 2025] INFO : Inicio del sistema.
[Tue Dec  2 22:30:42 2025] WARNING : Uso elevado de memoria detectado.
[Tue Dec  2 22:30:42 2025] ERROR : No se pudo conectar al servidor.
[Tue Dec  2 22:30:42 2025] INFO : [Modulo A] Cargando configuraciones...
[Tue Dec  2 22:30:42 2025] WARNING : [Modulo B] Tiempo de respuesta lento.
[Tue Dec  2 22:30:42 2025] ERROR : Fallo crítico en el módulo C
```

## Características Implementadas

### Filtrado por Nivel

El logger permite establecer un nivel mínimo de registro. Los mensajes con nivel inferior no se escriben en el archivo:

```cpp
logger->setNivelMinimo(WARNING);
logger->log(INFO, "No se registra");     // Ignorado
logger->log(ERROR, "Sí se registra");    // Escrito
```

### Modo Append

El archivo se abre con `ios::app`, preservando logs de ejecuciones anteriores y evitando pérdida de información.

### Timestamping Automático

Cada mensaje incluye automáticamente la fecha y hora exacta del evento, facilitando auditorías y depuración.

## Demostración en main()

El programa principal simula:

1. Registro de eventos con diferentes niveles de severidad
2. Logs desde múltiples módulos (A, B, C)
3. Cambio dinámico del nivel mínimo
4. Filtrado automático de mensajes según configuración

### Flujo de Ejecución

```cpp
Logger* logger = Logger::getInstancia();

// Configurar nivel mínimo a INFO
logger->setNivelMinimo(INFO);

// Registrar eventos de diferentes niveles
logger->log(INFO, "Inicio del sistema.");
logger->log(WARNING, "Uso elevado de memoria detectado.");
logger->log(ERROR, "No se pudo conectar al servidor.");

// Logs desde diferentes módulos
logger->log(INFO, "[Modulo A] Cargando configuraciones...");
logger->log(WARNING, "[Modulo B] Tiempo de respuesta lento.");

// Cambiar nivel mínimo a WARNING
logger->setNivelMinimo(WARNING);
logger->log(INFO, "Este mensaje no debe registrarse.");  // Filtrado
logger->log(ERROR, "Fallo critico en el módulo C");      // Se registra
```

## Casos de Uso

Este sistema es ideal para:

- Auditoría de aplicaciones en producción
- Depuración y diagnóstico de errores
- Monitoreo de sistemas en tiempo real
- Registro de eventos críticos
- Seguimiento de operaciones del sistema
- Análisis post-mortem de fallos
- Cumplimiento de normativas (logging obligatorio)

## Ventajas

- **Centralización**: Un único punto de registro para toda la aplicación
- **Consistencia**: Formato uniforme de todos los logs
- **Eficiencia**: Evita múltiples archivos abiertos simultáneamente
- **Filtrado**: Permite controlar el volumen de logs
- **Persistencia**: Los logs se mantienen entre ejecuciones
- **Timestamps**: Facilita correlación temporal de eventos
- **Simplicidad**: Interfaz fácil de usar desde cualquier módulo

## Limitaciones

- **Thread-Safety**: No es seguro en entornos multithreaded sin mutex
- **Tamaño de Archivo**: Sin rotación, el archivo puede crecer indefinidamente
- **Filtrado Global**: El nivel mínimo afecta todos los módulos por igual
- **Destino Único**: Solo escribe a archivo, no a consola o red
- **Sin Buffering**: Escritura inmediata puede afectar rendimiento
- **Formato Fijo**: No permite personalizar el formato de salida

## Conclusión

Este ejercicio demuestra una implementación básica pero funcional de un sistema de logging usando el patrón Singleton. Aunque simple, establece las bases para entender los conceptos de logging centralizado y puede ser extendido con características más avanzadas según las necesidades del proyecto.
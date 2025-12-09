# Ejercicio 3: Conexión a Base de Datos

## Descripción

Este ejercicio simula un sistema de gestión de conexiones a base de datos utilizando el patrón Singleton. Garantiza que solo exista una conexión activa a la vez, previniendo problemas de recursos y manteniendo el control del estado de la conexión.

## Patrón de Diseño

**Singleton para Gestión de Recursos Compartidos**

Controla el acceso a un recurso limitado (conexión a BD), asegurando que múltiples componentes no creen conexiones redundantes o conflictivas. Este patrón es especialmente útil cuando el recurso es costoso de crear o tiene limitaciones de cantidad.

## Estructura del Código

### Atributos de Estado

```cpp
private:
    static ConexionBD* instancia;
    bool conectado;
    string usuarioActual;
    int consultasEjecutadas;
```

- `conectado`: Flag booleano que indica el estado de la conexión
- `usuarioActual`: Almacena el nombre del usuario conectado
- `consultasEjecutadas`: Contador global de consultas SQL ejecutadas

### Componentes Principales

- **Constructor Privado**: Inicializa el estado desconectado
- **Instancia Estática**: Única instancia de conexión
- **Control de Estado**: Máquina de estados simple (conectado/desconectado)
- **Autenticación Básica**: Validación de credenciales simulada

## Funcionalidades

### Métodos Públicos

```cpp
static ConexionBD* getInstancia();
void conectar(const string& usuario, const string& password);
void ejecutarConsulta(const string& query);
void desconectar();
void estado();
```

- `getInstancia()`: Obtiene la única instancia de conexión
- `conectar(usuario, password)`: Establece conexión con autenticación
- `ejecutarConsulta(query)`: Ejecuta consultas SQL (simuladas)
- `desconectar()`: Cierra la conexión activa
- `estado()`: Muestra información completa del estado actual

## Compilación y Ejecución

```bash
g++ conexionBD.cpp -o conexionBD
./conexionBD
```

## Salida Esperada

```
Intentando conectar con clave incorrecta...
Error: contraseña incorrecta.

Conectando con clave correcta...
Conexion establecida correctamente como 'admin'.

Intentando nueva conexion desde bd2...
Ya existe una conexion activa por el usuario 'admin'.

Ejecutando consulta: SELECT * FROM usuarios;
Ejecutando consulta: UPDATE productos SET precio = 50;

ESTADO DE LA BD
Conexion: Activa
Usuario: admin
Consultas ejecutadas: 2

Desconectando...
Desconectando usuario 'admin'...

ESTADO DE LA BD
Conexion: Inactiva
Consultas ejecutadas: 2

¿bd1 y bd2 son la misma instancia? Sí
```

## Flujo de Operación Detallado

### 1. Autenticación

El sistema valida las credenciales antes de establecer la conexión:

```cpp
bd->conectar("admin", "12345");  // Éxito - password correcto
bd->conectar("admin", "0000");   // Fallo - password incorrecto
```

**Contraseña simulada**: "12345"

Mensajes de respuesta:
- Éxito: `"Conexion establecida correctamente como 'admin'."`
- Fallo: `"Error: contraseña incorrecta."`

### 2. Prevención de Conexiones Múltiples

El patrón Singleton garantiza que solo una conexión esté activa. Si se intenta una segunda conexión mientras existe una activa:

```cpp
bd1->conectar("admin", "12345");     // Primera conexión - Éxito
bd2->conectar("usuario2", "12345");  // Segunda conexión - Rechazada
```

Mensaje de rechazo:
```
Ya existe una conexion activa por el usuario 'admin'.
```

Este comportamiento previene:
- Conflictos de transacciones
- Consumo excesivo de recursos del servidor
- Inconsistencias en el estado de la base de datos

### 3. Ejecución de Consultas

Las consultas SQL solo se ejecutan si hay una conexión activa:

```cpp
bd->ejecutarConsulta("SELECT * FROM usuarios;");
bd->ejecutarConsulta("UPDATE productos SET precio = 50;");
```

**Con conexión activa**:
```
Ejecutando consulta: SELECT * FROM usuarios;
Ejecutando consulta: UPDATE productos SET precio = 50;
```

**Sin conexión activa**:
```
No hay conexion activa. No se puede ejecutar la consulta.
```

Cada consulta ejecutada incrementa el contador global `consultasEjecutadas`.

### 4. Seguimiento de Estadísticas

El método `estado()` proporciona un resumen completo:

```cpp
bd->estado();
```

Salida cuando está conectado:
```
ESTADO DE LA BD
Conexion: Activa
Usuario: admin
Consultas ejecutadas: 2
```

Salida cuando está desconectado:
```
ESTADO DE LA BD
Conexion: Inactiva
Consultas ejecutadas: 2
```

Note que el contador de consultas **persiste** incluso después de desconectar, proporcionando métricas globales de uso.

### 5. Desconexión

```cpp
bd->desconectar();
```

Comportamiento:
- Si hay conexión activa: la cierra y limpia el estado
- Si no hay conexión: informa que no hay nada que cerrar

## Demostración en main()

El programa principal demuestra todos los casos de uso:

```cpp
int main() {
    // 1. Obtener instancias (ambas apuntan al mismo objeto)
    ConexionBD* bd1 = ConexionBD::getInstancia();
    ConexionBD* bd2 = ConexionBD::getInstancia();

    // 2. Intento fallido con credenciales incorrectas
    bd1->conectar("admin", "0000");

    // 3. Conexión exitosa
    bd1->conectar("admin", "12345");

    // 4. Intento de segunda conexión (rechazado)
    bd2->conectar("usuario2", "12345");

    // 5. Ejecución de consultas
    bd1->ejecutarConsulta("SELECT * FROM usuarios;");
    bd1->ejecutarConsulta("UPDATE productos SET precio = 50;");

    // 6. Verificación de estado
    bd2->estado();

    // 7. Desconexión
    bd2->desconectar();

    // 8. Verificación final de estado
    bd1->estado();

    // 9. Confirmación de instancia única
    cout << "¿bd1 y bd2 son la misma instancia? "
         << ((bd1 == bd2) ? "Sí" : "No") << endl;

    return 0;
}
```


#include <iostream>
#include <string>
using namespace std;

class Configuracion {
private:
    string idioma;
    string zonaHoraria;

    // 1. Constructor privado
    Configuracion() : idioma("ES"), zonaHoraria("GMT-5") {}

    // 2. Instancia estática única
    static Configuracion* instancia;

public:
    // 3. Prohibir copia
    Configuracion(const Configuracion&) = delete;
    void operator=(const Configuracion&) = delete;

    // 4. Método de acceso al Singleton
    static Configuracion* getInstancia() {
        if (instancia == nullptr) {
            instancia = new Configuracion();
        }
        return instancia;
    }

    void mostrar_configuracion() {
        cout << "Idioma: " << idioma << endl;
        cout << "Zona horaria: " << zonaHoraria << endl;
    }

    // Métodos set
    void setIdioma(string id) { idioma = id; }
    void setZona(string zh) { zonaHoraria = zh; }
};

// Definición de la instancia
Configuracion* Configuracion::instancia = nullptr;

int main() {
    Configuracion* c1 = Configuracion::getInstancia();
    Configuracion* c2 = Configuracion::getInstancia();

    c1->setIdioma("EN");
    c1->setZona("UTC");

    cout << "Configuracion desde c1:" << endl;
    c1->mostrar_configuracion();

    cout << "\nConfiguracion desde c2 (misma instancia):" << endl;
    c2->mostrar_configuracion();

    cout << "\n¿c1 y c2 son el mismo objeto? ";
    cout << ((c1 == c2) ? "Sí" : "No") << endl;

    return 0;
}

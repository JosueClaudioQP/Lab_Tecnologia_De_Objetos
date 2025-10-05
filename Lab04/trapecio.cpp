#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
using namespace std;

class Funcion {
public:
    virtual double evaluar(double x) const = 0;
    virtual ~Funcion() = default;
};

class FuncionCuadratica : public Funcion {
public:
    double evaluar(double x) const override {
        return 2.0 * x * x + 3.0 * x + 0.5;
    }
};

class IntegradorTrapecio {
private:
    double a, b;
    long n;
    const Funcion& funcion;

public:
    IntegradorTrapecio(double a_, double b_, long n_, const Funcion& funcion_)
        : a(a_), b(b_), n(n_), funcion(funcion_) {}

    double integrar() const {
        double h = (b - a) / n;
        double sumaTotal = 0.5 * (funcion.evaluar(a) + funcion.evaluar(b));

        for (long i = 1; i < n; ++i) {
            double x = a + i * h;
            sumaTotal += funcion.evaluar(x);
        }

        return sumaTotal * h;
    }
};

int main() {
    double a = 2.0;
    double b = 20.0;
    long n = 1000000;

    FuncionCuadratica funcion;
    IntegradorTrapecio integrador(a, b, n, funcion);

    auto inicio = chrono::high_resolution_clock::now();
    double resultado = integrador.integrar();
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duracion = fin - inicio;

    cout.precision(14);
    cout << fixed;
    cout << "Integral aproximada (Trapecio) = " << resultado << endl;
    cout << "Subintervalos = " << n << ", Tiempo = " << duracion.count() << " ms" << endl;

    return 0;
}

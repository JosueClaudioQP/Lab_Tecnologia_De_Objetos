#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

class Funcion {
public:
    virtual double evaluar(double x) const {
        return 2.0 * x * x + 3.0 * x + 0.5;
    }

    virtual ~Funcion() = default;
};

class IntegradorTrapecioParalelo {
private:
    double a, b;
    long n;
    int numHilos;
    const Funcion& funcion;

    void integrarParcial(double h, long inicio, long fin, long double& resultadoParcial) const {
        long double suma = 0.0;
        for (long i = inicio; i <= fin; ++i) {
            double x = a + i * h;
            suma += funcion.evaluar(x);
        }
        resultadoParcial = suma;
    }

public:
    IntegradorTrapecioParalelo(double a_, double b_, long n_, int numHilos_, const Funcion& funcion_)
        : a(a_), b(b_), n(n_), numHilos(numHilos_), funcion(funcion_) {}

    long double integrar() const {
        double h = (b - a) / n;
        long double sumaTotal = 0.5L * (funcion.evaluar(a) + funcion.evaluar(b));

        vector<thread> hilos(numHilos);
        vector<long double> resultados(numHilos, 0.0);

        long pasosPorHilo = n / numHilos;

        for (int i = 0; i < numHilos; ++i) {
            long inicio = i * pasosPorHilo + 1;
            long fin = (i == numHilos - 1) ? (n - 1) : ((i + 1) * pasosPorHilo);

            hilos[i] = thread(&IntegradorTrapecioParalelo::integrarParcial, this,
                              h, inicio, fin, ref(resultados[i]));
        }

        for (int i = 0; i < numHilos; ++i) {
            hilos[i].join();
            sumaTotal += resultados[i];
        }

        return sumaTotal * h;
    }
};

int main() {
    double a = 2.0, b = 20.0;
    long n = 1000000;
    int numHilos = 4;

    Funcion funcion;

    IntegradorTrapecioParalelo integrador(a, b, n, numHilos, funcion);

    auto inicio = chrono::high_resolution_clock::now();
    long double resultado = integrador.integrar();
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duracion = fin - inicio;

    cout.precision(15);
    cout << "Integral aproximada (Trapecio paralelo) = " << (double)resultado << endl;
    cout << "Subintervalos = " << n << ", Hilos = " << numHilos
         << ", Tiempo = " << duracion.count() << " ms" << endl;

    return 0;
}

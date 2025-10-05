#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

double f(double x){
    return 2.0 * x * x + 3.0 * x + 0.5;
}

double integrarPorTrapecio(double a, double b, long n){
    double h = (b - a)/n;
    double suma_total = 0.5 * (f(a) + f(b));
    double* valores = new double[n - 1];
    for(long i = 1; i < n; i++){
        double x = a + i * h;
        valores[i - 1] = f(x);
    }
    for(long i = 0; i < n - 1; i++){
        suma_total += valores[i];
    }
    double resultado = suma_total * h;
    delete[] valores;
    return resultado;
}

int main(){
    double a = 2.0;
    double b = 20.0;
    long n = 1000000;

    auto inicio = chrono::high_resolution_clock::now();
    double resultado = integrarPorTrapecio(a, b, n);
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duracion = fin - inicio;

    cout.precision(14);
    cout << fixed;
    cout << "Integral aproximada (Trapecio) = " << resultado << endl;
    cout << "Subintervalos = " << n << ", Tiempo = " << duracion.count() << " ms" << endl;

    return 0;
}
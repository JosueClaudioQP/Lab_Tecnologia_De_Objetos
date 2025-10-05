#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

double f(double x){
    return 2.0 * x * + 3.0 * x + 0.5;
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
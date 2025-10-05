#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
using namespace std;

double f(double x){
    return 2.0 * x * x + 3.0 * x + 0.5;
}

void integrarParcial(double a, double h, long inicio, long fin, long double &resultado_parcial) {
    long double suma = 0.0;
    for(long i = inicio; i <= fin; i++){
        double x = a + i * h;
        suma += f(x);
    }
    resultado_parcial = suma;
}

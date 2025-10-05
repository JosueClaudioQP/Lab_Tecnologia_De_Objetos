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

long double integrarPoTrapecioParalelo(double a, double b, long n, int num_hilos) {
    double h = (b - a) / n;
    long double suma_total = 0.5L * (f(a) + f(b));

    thread* hilos = new thread[num_hilos];
    long double* resultados = new long double[num_hilos];

    long pasos_por_hilo = n / num_hilos;

    for (int i = 0; i < num_hilos; i++) {
        long inicio = i * pasos_por_hilo + 1;
        long fin = (i == num_hilos - 1) ? (n - 1) : ((i + 1) * pasos_por_hilo);
        hilos[i] = thread(integrarParcial, a, h, inicio, fin, ref(resultados[i]));
    }

    for (int i = 0; i < num_hilos; i++) {
        hilos[i].join();
        suma_total += resultados[i];
    }

    delete[] hilos;
    delete[] resultados;

    return suma_total * h;
}

package main

import (
	"fmt"
	"sync"
	"time"
)

type Funcion interface {
	Evaluar(x float64) float64
}

type FuncionCuadratica struct{}

func (f FuncionCuadratica) Evaluar(x float64) float64 {
	return 2.0*x*x + 3.0*x + 0.5
}

type IntegradorTrapecioParalelo struct {
	a, b     float64
	n        int64
	numHilos int
	funcion  Funcion
}

func (it IntegradorTrapecioParalelo) integrarParcial(h float64, inicio, fin int64, wg *sync.WaitGroup, resultado *float64, mutex *sync.Mutex) {
	defer wg.Done()

	suma := 0.0
	for i := inicio; i <= fin; i++ {
		x := it.a + float64(i)*h
		suma += it.funcion.Evaluar(x)
	}

	mutex.Lock()
	*resultado += suma
	mutex.Unlock()
}

func (it IntegradorTrapecioParalelo) Integrar() float64 {
	h := (it.b - it.a) / float64(it.n)
	sumaTotal := 0.5 * (it.funcion.Evaluar(it.a) + it.funcion.Evaluar(it.b))

	var resultado float64 = 0.0
	var wg sync.WaitGroup
	var mutex sync.Mutex

	pasosPorHilo := it.n / int64(it.numHilos)

	for i := 0; i < it.numHilos; i++ {
		inicio := int64(i)*pasosPorHilo + 1
		var fin int64
		if i == it.numHilos-1 {
			fin = it.n - 1
		} else {
			fin = (int64(i+1) * pasosPorHilo)
		}

		wg.Add(1)
		go it.integrarParcial(h, inicio, fin, &wg, &resultado, &mutex)
	}

	wg.Wait()
	sumaTotal += resultado
	return sumaTotal * h
}

func main() {
	a := 2.0
	b := 20.0
	n := int64(1_000_000)
	numHilos := 4

	funcion := FuncionCuadratica{}
	integrador := IntegradorTrapecioParalelo{
		a:        a,
		b:        b,
		n:        n,
		numHilos: numHilos,
		funcion:  funcion,
	}

	inicio := time.Now()
	resultado := integrador.Integrar()
	duracion := time.Since(inicio)

	fmt.Printf("Integral aproximada (Trapecio paralelo) = %.15f\n", resultado)
	fmt.Printf("Subintervalos = %d, Hilos = %d, Tiempo = %.3f ms\n", n, numHilos, float64(duracion.Microseconds())/1000.0)
}

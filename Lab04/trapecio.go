package main

import (
	"fmt"
	"time"
)

type Funcion interface {
	Evaluar(x float64) float64
}

type FuncionCuadratica struct{}

func (f FuncionCuadratica) Evaluar(x float64) float64 {
	return 2.0*x*x + 3.0*x + 0.5
}

type IntegradorTrapecio struct {
	a, b   float64
	n      int64
	funcion Funcion
}

func (it IntegradorTrapecio) Integrar() float64 {
	h := (it.b - it.a) / float64(it.n)
	sumaTotal := 0.5 * (it.funcion.Evaluar(it.a) + it.funcion.Evaluar(it.b))

	for i := int64(1); i < it.n; i++ {
		x := it.a + float64(i)*h
		sumaTotal += it.funcion.Evaluar(x)
	}

	return sumaTotal * h
}

func main() {
	a := 2.0
	b := 20.0
	n := int64(1000000)

	funcion := FuncionCuadratica{}
	integrador := IntegradorTrapecio{
		a: a,
		b: b,
		n: n,
		funcion: funcion,
	}

	inicio := time.Now()
	resultado := integrador.Integrar()
	duracion := time.Since(inicio)

	fmt.Printf("Integral aproximada (Trapecio) = %.14f\n", resultado)
	fmt.Printf("Subintervalos = %d, Tiempo = %.3f ms\n", n, float64(duracion.Microseconds())/1000.0)
}

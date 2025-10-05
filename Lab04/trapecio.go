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
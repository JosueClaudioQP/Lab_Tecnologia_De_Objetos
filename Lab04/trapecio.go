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
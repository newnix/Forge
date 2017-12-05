package main

import (
	"fmt"
	"math"
)

func pow(x, n, lim float64) float64 {
	/* v is defined only for the scope of the if statement */
	if v := math.Pow(x, n); v < lim {
		return v
	}
	return lim
}

func main() {
	fmt.Println(
		pow(3, 2, 10),
		pow(3, 3, 20),
	)
}

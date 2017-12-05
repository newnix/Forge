package main

import (
	"fmt"
	"math"
)

func sqrt(x float64) string {
	/* like the for loop, if statements don't need parens, but do need braces */
	if x < 0 {
		return sqrt(-x) + "i"
	}
	return fmt.Sprint(math.Sqrt(x))
}

func main() {
	fmt.Println(sqrt(2), sqrt(-4))
}

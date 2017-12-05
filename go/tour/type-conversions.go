package main

import (
	"fmt"
	"math"
)

/* 
 * in golang, type conversions must be explicitly
 * cast, unlike in C where some conversions can be 
 * handled automatically
 */

func main() {
	var x, y int = 3, 4
	var f float64 = math.Sqrt(float64(x*x + y*y))
	var z uint = uint(f)
	fmt.Println(x, y, z)
}

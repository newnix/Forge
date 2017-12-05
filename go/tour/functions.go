package main

import "fmt"

/* 
 * according to the golang tour, this could be 
 * expressed as:
 * func add (x, y int)
 * instead with the same functionality
 */
func add(x int, y int) int {
	return x+y
}

func main() {
	fmt.Println(add(42,13))
}

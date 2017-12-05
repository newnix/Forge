package main

import "fmt"

/* 
 * In golang, all variables that aren't initialized
 * are set to 0, much like the C standard demands.
 */
func main() {
	var i int
	var f float64
	var b bool
	var s string
	fmt.Printf("%v %v %v %q\n", i, f, b, s)
}

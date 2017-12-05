package main

import "fmt"

/* 
 * functions can return an arbitrary number of 
 * results in golang
 */

func swap (x, y string) (string, string) {
	return y, x
}

func main() {
	a, b := swap("hello", "world")
	fmt.Println(a,b)
}

package main

import "fmt"

/* 
 * the var statement declares a list of variables.
 * as in function type lists, the type is last. 
 * essentially like writitng C variable lists backwards
 */
var c, python, java bool

func main() {
	var i int
	fmt.Println(i, c, python, java)
}

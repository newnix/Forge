package main

import "fmt"

/* 
 * since these variables are assigned the values
 * 1, 2 they do not need to be declared of type 'int'
 * in golang, when initializing a variable, the variable
 * takes the type of the initializer
 */
var i, j int = 1, 2

func main() {
	var c, python, java = true, false, "no!"
	fmt.Println(i, j, c, python, java)
}

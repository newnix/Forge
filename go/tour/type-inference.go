package main

import "fmt"

/* 
 * simple example of golang type inference, 
 * however this makes compilation take much longer
 */
func main() {
	v := 42
	fmt.Printf("v is of type %T\n", v)
}

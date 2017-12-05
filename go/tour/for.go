package main

import "fmt"

/* 
 * This will display the only looping operation 
 * supported in golang, the for loop
 */

func main() {
	sum := 0
	for i := 0; i < 10 ; i++ {
		sum += i
	}
	fmt.Println(sum)
}

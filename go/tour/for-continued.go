package main

import "fmt"

func main() {
	sum := 1
	/* Apparently the first and third elements of a for loop are optional */
	for ; sum < 1000; {
		sum += sum
	}
	fmt.Println(sum)
}

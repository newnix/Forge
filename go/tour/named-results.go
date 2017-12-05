package main

import "fmt"

func split(sum int) (x, y int) {
	x = sum * 4/9
	y = sum - x
	/*
	 * This is what's known as a "naked return", it
	 * returns the named return values, in this case x and y
	 * this is to be avoided wherever possible as it leads to 
	 * less readable code. 
	 */
	return
}

func main() {
	fmt.Println(split(17))
}

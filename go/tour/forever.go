package main

import "fmt"

func main() {
	for {
		/* this will only die when you send sigint */
		fmt.Println("You must send sigint or sigterm to kill this process")
		for i := 0; i < 100; i++ {
		}
	}
}

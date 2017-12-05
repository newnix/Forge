package main

import "fmt"

const (
	/* 
	 * Create a huge number by shifting a single bit 
	 * left by 100 places. In other words, the binary 
	 * number 1 followed by 100 zeros
	 */
	 Big = 1 << 100
	 /* and now shift it back 99 places, which should = 2 */
	 Small = Big >> 99
)

func needInt(x int) int { return x*10 + 1}
func needFloat(x float64) float64 {
	return x * 0.1
}

func main() {
	fmt.Println(needInt(Small))
	fmt.Println(needFloat(Small))
	fmt.Println(needFloat(Big))
}

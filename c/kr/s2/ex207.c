/* 
 * Exercise 2-7 from K&R's ANSI C
 * meant to write a function called invert(x,p,n)
 * that returns x with the n bits that begin at position p inverted (ie 0->1 && 1->0)
 *
 * More bitwise learning
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"

unsigned short int flipbits(unsigned short int x, unsigned short int p, unsigned short int n);

int main()
{
	unsigned short int result;
	unsigned short int x, p, n; /* our vars */
	x = 10;
	p = 2;
	n = 3;

	/* calculate the value once, for easy use later */
	result = flipbits(x,p,n);
	/* print the result in decimal and hex notation */	
	printf("Result is %hu\t(%hX)\n",result,result);

	return 0;
}

unsigned short int flipbits(unsigned short int x, unsigned short int p, unsigned short int n)
{
	/* 
	 * Meant to flip the n bits starting at p in x
	 * EX: x = 10, p = 2, n = 3
	 * x = 00000000 00001010
	 * return 00000000 00000100 = 4
	 */
	
	return (1 ^ (x ^ ~(~0 << (p+n -1))));
	/*
	 * 00000000 00001010 ^ ~(~0 << (2+3-1))
	 * 00000000 00001010 ^ ~(~0 << 4)
	 * 00000000 00001010 ^ ~(11111111 11111111 << 4)
	 * 00000000 00001010 ^ ~(11111111 11110000)
	 * 00000000 00001010 ^ 00000000 00001111
	 * 00000000 00000101
	 *
	 * the final XOR against 1 is meant to get rid of the trailing +1,
	 * seems to be working just fine so far.
	 *
	 * 1 ^ (00000000 00001010 ^ ~(~0 << (2+3 -1)))
	 * 1 ^ (00000000 00001010 ^ ~(11111111 11111111 << 4))
	 * 1 ^ (00000000 00001010 ^ ~(11111111 11110000))
	 * 1 ^ (00000000 00001010 ^ 00000000 00001111)
	 * 1 ^ (00000000 00000101)
	 * 11111111 11111111 ^ 00000000 00000101
	 * 00000000 00000100 = 4
	 *
	 * Unless I'm mistaken, this should work to flip any arbitrary bits on any arbitrary word size
	 * as the function definition and explanation shows starting at line 34
	 */
}

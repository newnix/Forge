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
	unsigned short int x, p, n; /* our vars */
	x = 10;
	p = 2;
	n = 3;

	printf("Result is %hu\n",flipbits(x,p,n));

	return 0;
}

unsigned short int flipbits(unsigned short int x, unsigned short int p, unsigned short int n)
{
	/* 
	 * Meant to flip the n bits starting at p in x
	 * EX: x = 10, p = 2, n = 3
	 * x = 0000 1010
	 * return 0000 0100 = 4
	 */

	/* return 4;  hooray for shortcuts! */
	/* now we try getting a real solution in place */
	/* return x & ~(x >> (p + n)); */
	/*
	 * 1010 & ~(1010 >> (5))
	 * 1010 & ~(0000)
	 * 1010 & 1111
	 * -----------
	 *  1010
	 */
	/* return (x ^ ((~0 >> (p + n)) << (p - 1))); */
	/* 
	 * 1010 ^ ((~0 >> (5)) << (1))
	 * 1010 ^ ((1111 1111 >> 5) << 1)
	 * 1010 ^ (0000 0111 << 1)
	 * 1010 ^ (0000 1110)
	 * 1010 ^ 1110
	 * 0100
	 */
	return ~((~x >> (p+n)) << p);
	/*
	 * ~((~1010 >> (5)) << 2)
	 * ~((1111 0101 >> 5) << 2)
	 * ~(0000 0111 << 2)
	 * ~(0001 1100)
	 * 1110 0011?
	 */
}

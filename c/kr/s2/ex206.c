/*
 * Exercise 2-6 in K&R's ANSI C
 * meant to create a function called setbits(x,p,n,y)
 * returns x with the n bits that begin at position p set to the rightmost n bits of y,
 * leaving other bits unchanged.
 *
 * Basically a clusterfuck of bitwise operators. This is going to be interesting.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"

/*
 * There's a skeleton/example function of the same name listed like so:
 *
 * unsigned getbits(unsigned x, int p, int n)
 * {
 * 	return (x >> (p+1-n)) & ~(~0 << n);
 * }
 * This should be evaluated like the following:
 * x rightshifted to p + 1 - n bits
 * AND
 * MAX leftshifted n bits, then flipped again
 * so if x = p = n = 2
 * 2 >> 1 bits AND 1100 = 0001 & 1100 = 0;
 */
unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y);

int main()
{
	unsigned int x, p;
	x = 2;
	p = 1;
	/* do things */
	printf("%d\n",setbits(x,p,x,p));
	return 0;
}

unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y)
{
	/* 
	 * this should return x
	 * with the n bits from p 
	 * set to the rightmost n bits of y
	 *
	 * so if x = 1100 0011, n = 2, p = 2, y = 2
	 * this should return something like 
	 * 11001100, if I'm right.
	 */
	return x & p;
	/* I know this is wrong, but I want to have something here */
}

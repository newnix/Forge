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
 * unsigned short getbits(unsigned short x, int p, int n)
 * {
 * 	return (x >> (p+1-n)) & ~(~0 << n);
 * }
 * This should be evaluated like the following:
 * x rightshifted to p + 1 - n bits
 * AND
 * MAX leftshifted n bits, then flipped again (1111 1111 << 2 = 1111 1100; ~11111100 = 0011)
 * so if x = p = n = 2
 * 2 >> 1 bits AND 1100 = 0001 & 0011 = 1;
 */
unsigned short int setbits(unsigned short int x, unsigned short int p, unsigned short int n, unsigned short int y);

int main()
{
	unsigned short int x, p, n, y;
	x = 2;
	p = 1;
	y = 3;
	n = 2;
	/* do things */
	printf("%u\n",setbits(x,p,n,y));
	return 0;
}

unsigned short int setbits(unsigned short int x, unsigned short int p, unsigned short int n, unsigned short int y)
{
	/* 
	 * this should return x
	 * with the n bits from p 
	 * set to the rightmost n bits of y
	 *
	 * if x = y = p = n = 2;
	 * ....
	 */
	return ((y & ~0 ) ^ (x >> (p + n - 1)));
	/* I know this is wrong, but I want to have something here */
}

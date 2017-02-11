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
 */
unsigned int setbits(int x, int p, int n, int y);

int main()
{
	/* do things */

	return 0;
}

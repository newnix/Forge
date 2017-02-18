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

unsigned int flipbits(unsigned int x, unsigned int p, unsigned int n);

int main()
{
	unsigned int x, p, n; /* our vars */
	x = 10;
	p = 2;
	n = 3;

	printf("Result is %u\n",flipbits(x,p,n));

	return 0;
}

unsigned int flipbits(unsigned int x, unsigned int p, unsigned int n)
{
	/* 
	 * Meant to flip the n bits starting at p in x
	 * EX: x = 10, p = 2, n = 3
	 * x = 0000 1010
	 * return 0000 0100 = 4
	 */

	/* return 4;  hooray for shortcuts! */
	/* now we try getting a real solution in place */
	return x & ~(x >> (p + n));
}

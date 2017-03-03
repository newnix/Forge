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
	unsigned short int x, p, n, y, res;
	x = 11;
	p = 2;
	y = 3;
	n = 2;
	res = setbits(x,y,n,p);
	/* do things */
	printf("%hu\t(%hX)\n",res,res);
	return 0;
}

unsigned short int setbits(unsigned short int x, unsigned short int p, unsigned short int n, unsigned short int y)
{
	/* 
	 * this should return x
	 * with the n bits from p 
	 * set to the rightmost n bits of y
	 *
	 * x = 11, p = 2, y = 3, n = 2
	 * x = 00000000 00001011
	 * return 00000000 00001010
	 */
	unsigned short int max;

	/* 
	 * sanity check here, helps ensure that if this program becomes interactive,
	 * I'll actually be able to handle input for 'n' correctly. 
	 * should be doing the same for any values accepted from the user, else I'll have to truncate
	 */
	max = ((8 * sizeof(x)) - 1);
	printf("n:%hu\tmax:%hu\n",n,max);
	if (n > max)
	{
		return 500;
	} 
	/* currently, this should isolate the bits meant to be manipulated */
	return (x << (max - (n + p))) >> (max - (1 + y + n));
	/* I know this is wrong, but I want to have something here */
}

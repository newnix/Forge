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
	
	printf("Result is %hu\t(%hX)\n",result,result);

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
	/* return ~(x ^ ((~0 >> (p + n)) << (p - 1))); */
	/* 
	 * (1010 ^ ((~0 >> (5)) << (2)))
	 * (1010 ^ ((1111 1111 >> 5) << 2))
	 * (1010 ^ ((0000 0111 << 2)))
	 * (1010 ^ (0001 1100)
	 * (0000 1010 ^ 0001 1100)
	 * (0001 0100)
	 */
	return ((~x >> (p+n)) << p);
	/*
	 * ~((~0000 1010 >> (2 + 3)) << 2)
	 * ~((1111 0101 >> 5) << 2)
	 * ~(0000 0111 << 2)
	 * ~(0001 1100)
	 * 1110 0011
	 * ---------
	 * This must be wrong, because it's returning 3 (0000 0011)
	 * --------
	 * 3 = 0011 but ~3 = 65532/FFFC
	 * so the short int should be 4 bytes
	 * which explains why the values are so far off of my estimates
	 * 11111111 111111111 11111111 11111111
	 * so the process would be more like the following:
	 *
	 * ((~(00000000 00000000 00000000 00001010) >> (5)) << 2)
	 * (((11111111 11111111 11111111 11110101) >> 5) << 2)
	 * ((00000111 11111111 11111111 11111111) << 2)
	 * ( 00011111 11111111 11111111 11111100)
	 * ... the inverse of this number is not 3... so my word size must be wrong still.
	 * after some testing, the word size for short ints is 2 bytes, not 4.
	 *
	 * This makes my un-flipped result 11111111 11111100, which when flipped is 3.
	 */
}

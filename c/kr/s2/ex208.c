/* 
 * Exercise 2-8 in K&R's ANSI C 
 * Meant to create a function called rightrot(x,n)
 * that returns the value of the integer x rotated to the right by n bit positions
 * so if x = 10, n = 3
 * 00000000 00001010, 3
 * return 01000000 00000001
 * hooray for bitwise operations!
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"

unsigned short int rrot(unsigned short int x, unsigned short int n);

int main()
{
	/*
	 * first let's test this on some statically assigned values
	 */

	unsigned short int x, n, result;
	x = 10;
	n = 3;

	/* let's get the resulting int first, then print the resulting value */
	result = rrot(x,n);
	printf("Size of x: %zu, (%lu)\n",sizeof(x), ((sizeof(x) * 8) -1)); 
	/* now let's show the result in decimal and hex */
	printf("Right rotation of %hu (%hX) by %hu bits: %hu\t(%hX)\n",x,x,n,result,result);
}

unsigned short int rrot(unsigned short int x, unsigned short int n)
{
	/*
	 * rotate x to the right by n positions
	 * ex: x = 123456, n = 3
	 * return 456123, but in binary form.
	 */
	unsigned short int r, bitlen;
	r = 0;
	bitlen = (8 * sizeof(x) - 1); /* this should help maintain compatibility with larger primitives */
	/* this was taken from the wikipedia page explaining rotations, might need some reworking */
	/* the recommended method was r = (x << n) | (x >> (-n & bitlen)); */
	r = (x << (bitlen - n)) | (x >> n);
	/* 
	 * 00000000 00001010 rotated to the right by 3 -> 01000000 00000001
	 * should be a few thousand, with an odd number at the end.
	 *
	 * 00000000 00001010 << 3 | 00000000 00001010 >> 13
	 * 00000000 01010000 | 0
	 * 00000000 01010000 = 80 (2^6 + 2^4)
	 *
	 * accidentally followed the instructions for a left rotation, though this has simplified the rest of the excersize
	 */
	
	return (r);
}

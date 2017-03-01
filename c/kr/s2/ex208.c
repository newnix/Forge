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
#include "../get_line.h"

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

	/* now let's show the result in decimal and hex */
	printf("Right rotation of %hu by %hu bits: %hu\t(%hX)\n",x,n,result,result);
}

unsigned short int rrot(unsigned short int x, unsigned short int n)
{
	/*
	 * rotate x to the right by n positions
	 * ex: x = 123456, n = 3
	 * return 456123, but in binary form.
	 */
	unsigned short int r;
	r = 0;
	
	
	return (r);
}

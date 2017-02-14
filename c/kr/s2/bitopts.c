/* 
 * This is meant to give me an idea of how the various bitwise operations work
 * Examples are being taken from pages 48 & 49 in K&R's ANSI C
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	static unsigned const short x = 10; /* our value to play with */
	
	printf("Starting value is: integer: %hu | hex: %hx (binary value 0000 1010)\n",x,x);
	/* now we need to do some bitwise ops on it */
	printf("First: Bitwise AND, result is 1 if both a and b are 1.\nex: 1010 & 1010 = 1010\n");
	printf("x & 10: integer: %hu | hex: %hx\n",(x & 10),(x & 10));
	printf("\nNext: Bitwise OR, result is 1 if either a or b are 1.\nex: 1010 | 1010 = 1010\n");
	printf("x | 10: integer: %hu | hex: %hx\n",(x | 10),(x | 10));
	printf("\nBitwise XOR, result is 1 when a and b are different.\nex: 1010 ^ 1010 = 0000\n");
	printf("x ^ 10: integer: %hu | hex: %hx\n",(x ^ 10), (x ^ 10));
	/*
	 * Rightshift operation, example given in the book states
	 * x >> 2 will shift the value of x to the right by 2, filling the vacated bits with 0
	 * so this should be equivalent to: 1010 >> 2 = 0010, or 2.
	 */
	printf("\nRightshift, will move x 2 bits to the right, filling vacated bits with 0s.\nex: 1010 >> 2 = 0010\n"); 
	printf("x >> 2: integer: %hu | hex: %hx\n",(x >> 2),(x >> 2));
	/*
	 * According to the book, the leftshift operation works identically 
	 * to the rightshift operation. So 1010 << 2 = 101000, or 80 (2^4 = 16 + 2^6 = 64)
	 */
	printf("\nLeftshift, identical to before, but in the opposite direction.\nex: 1010 << 2 = 101000\n");
	printf("x << 2: integer: %hu | hex: %hx\n",(x << 2),(x << 2));
	/* 
	 * This unary operator is meant to display the complementary value
	 * so each 1 becomes a 0 and vice-versa. The example in the book only shows
	 * x = x & ~077 which apparently sets the last six bits of x to 0, though I'm not sure how at this time.
	 * If I'm understanding it correctly something like: x = ~10
	 * would be the same as: x = ~00001010
	 * so x = 11110101, though I'm not sure why I'm getting something different in my output
	 * ^ Turns out it was due to using a signed int, sign bits are a thing to be wary of
	 */
	printf("\nUnary NOT operator, this inverts the bits of the argument, with the value \'10\' this should be SHORT_MAX-10\nex: ~00001010 = 11110101\n");
	printf("~x: integer: %hu | hex: %hx\n",(~x),(~x));
	return 0;
}

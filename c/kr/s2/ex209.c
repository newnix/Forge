/* 
 * Exercise 2-9 in K&R's ANSI C 2nd edition
 * Found on page 51
 *
 * In a two's complement number system, x &= (x-1)
 * deletes the rightmost 1-bit in x. Explain why.
 * Use this observation to write a faster version of bitcount
 */

#include <stdio.h>
#include <stdlib.h>

int countbits(unsigned int x);

int main()
{
	unsigned int x, count;
	x = ~0;

	count = countbits(x);
	printf("Total 1-bits in %u:\t%u\n",x,count);

	return 0;
}
/*
 * With binary operations, x &= (x-1) will always remove the right most 1-bit,
 * this is due to binary comprising of only 1's and 0's so if x = 1111, x-1 = 1110
 * so x & (x - 1) = 1110, and so on, until all bits are 0.
 * This means we don't need to shift every bit over and evaluate if it's 1 or 0, so for instances where 
 * x != ~0, this method should be faster to calculate the 1-bits than shifting and evaluating the result,
 * as we only need to iterate for as long as there's a 1 in the binary representation, rather than testing 
 * every single bit in the number.
 */
int countbits(unsigned int x)
{
	int b;
	for (b = 0; x != 0; x &= (x - 1))
	{
		b++; /* since we're not yet 0, we must've deted another 1-bit */
	}
	return b;
}

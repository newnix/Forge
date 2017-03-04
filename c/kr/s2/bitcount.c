/*
 * Bitcount, an example function found in K&R's ANSI C 2nd Edition
 * Page 50. 
 * This is meant to be made more efficient in ex209.c (exercise 2-9)
 */

#include <stdio.h>
#include <stdlib.h>

int bitcount(unsigned int x);

int main ()
{
	unsigned int x, count;
	x = ~0; /* might as well give us as many 1-bits as possible */
	count = bitcount(x);

	printf("Total 1-bits in %u:\t%u\n",x,count);
	return 0;
}

int bitcount(unsigned int x)
{
	int b;

	for (b = 0; x != 0; x >>= 1)
	{
		if (x & 01)
		{
			b++;
		}
	}
	return b;
}

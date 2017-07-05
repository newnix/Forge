/*
 * simple bit rotation tool to display which direction the bits are ordered
 * meant to be a simple way to determine endian-ness
 */

/* only necessary header */
#include <stdio.h>

/* here's where we get things done */
int
main (void) {
	short signed int start, lshift, rshift; /* the values to calculate and display, minimum size to get the needed data */
	start = 10; /* simple, predictable binary value using an int */
	lshift = start << 2; /* left shift twice */
	rshift = start >> 2; /* right shift twice */
	/* display the values */
	printf("Starting value: %hd\t%hX\n",start,start);
	printf("\nOn a little-endian system, the values should be represented as such:\n");
	printf("10 = 0xA = 0000 1010\n");
	printf("10 >> 2 = 0x2 = 0000 0010\n");
	printf("10 << 2 = 0x28 = 0010 1000\n");
	printf("\nOn a big-endian system, the values will instead be:\n");
	printf("10 = 0xA = 0101 0000\n");
	printf("10 >> 2 = 0x28 = 0001 0100\n");
	printf("10 << 2 = 0x2 = 0100 0000\n\n");
	printf("Left shifted value: %hd\t%hX\n",lshift,lshift);
	printf("Right shifted value: %hd\t%hX\n",rshift,rshift);
	return 0;
}
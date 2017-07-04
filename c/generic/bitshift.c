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
	printf("Left shifted value: %hd\t%hX\n",lshift,lshift);
	printf("Right shifted value: %hd\t%hX\n",rshift,rshift);
}
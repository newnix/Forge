/*
 * Determine the ranges of char, short, int, and long
 * both signed and unsigned 
 * This can be done by printing predefined values or by calculating them somehow
 */

#include <stdio.h>
/* the following headers contain implementation-specific values for data types */
#include <limits.h>
#include <float.h>
#include <stdlib.h>

int main()
{
	printf("Max size of an unsigned int:\t%u\n",UINT_MAX);
	printf("Min size of an unsigned int:\t%u\n",INT_MIN);
	printf("Max size of a signed int:\t%d\n",INT_MAX);
	printf("Min size of a signed int:\t%d\n",INT_MIN);
	printf("Max size of an unsigned short:\t%hu\n",USHRT_MAX);
	printf("Min size of an unsigned short:\t%hu\n",SHRT_MIN);
	printf("Min size of a signed short:\t%hd\n",SHRT_MIN);
	printf("Max size of a signed short:\t%hd\n",SHRT_MAX);
	printf("Max size of an unsigned long:\t%lu\n",ULONG_MAX);
	printf("Min size of an unsigned long:\t%lu\n",LONG_MIN);
	printf("Max size of a signed long:\t%ld\n",LONG_MAX);
	printf("Min size of a signed long:\t%ld\n",LONG_MIN);
	printf("Max size of an unsigned char:\t%u\n",UCHAR_MAX);
	printf("Min size of an unsigned char:\t%u\n",CHAR_MIN); /* apparently there was a typo that was difficult to see with the Terminess font */
	printf("Max size of a signed char:\t%d\n",CHAR_MAX);
	printf("Min size of a signed char:\t%d\n",CHAR_MIN);

	/* here we'll get the "word size" or bit-length of some of these primitives as well. */
	/* The following method was shamelessly stolen from https://en.wikipedia.org/wiki/sizeof */
	short int *shortint = (short int *) malloc(10 * sizeof(short int));
	printf("\nshort int word size: %hu, %zu\n", shortint, sizeof(short int));
	free(shortint); /* no need to hold onto it anymore */
	
	int *intsize = (int *) malloc(10 * sizeof(int));
	printf("int word size: %u, %zu\n", intsize, sizeof(int));
	free(intsize); /* no need to hold onto it anymore */
	
	/* and let's keep going so there's easy reference material in source code and binary form! */
	long int *lngsize = (long int *) malloc(10 * sizeof(long int));
	printf("long int word size: %lu, %zu\n", lngsize, sizeof(long int));
	free(lngsize);

	float *fltsize = (float *) malloc(10 * sizeof(float));
	printf("float word size: %zu, %zu\n", fltsize, sizeof(float));
	free(fltsize);

	double *dblsize = (double *) malloc(10 * sizeof(double));
	printf("double word size: %zu, %zu\n", dblsize, sizeof(double));
	free(dblsize);


	return 0;
}

/*
 * Determine the ranges of char, short, int, and long
 * both signed and unsigned 
 * This can be done by printing predefined values or by calculating them somehow
 */

#include <stdio.h>
/* the following headers contain implementation-specific values for data types */
#include <limits.h>
#include <float.h>

int main()
{
	printf("Max size of an unsigned int:\t%u\n",UINT_MAX);
	printf("Min size of an unsigned int:\t%u\n",INT_MIN);
	printf("Max size of a signed int:\t%d\n",INT_MAX);
	printf("Min size of a signed int:\t%d\n",INT_MIN);
	printf("Max size of an unsigned short:\t%u\n",USHRT_MAX);
	printf("Min size of an unsigned short:\t%u\n",SHRT_MIN);
	printf("Min size of a signed short:\t%d\n",SHRT_MIN);
	printf("Max size of a signed short:\t%d\n",SHRT_MAX);
	printf("Max size of an unsigned long:\t%u\n",ULONG_MAX);
	printf("Min size of an unsigned long:\t%u\n",LONG_MIN);
	printf("Max size of a signed long:\t%d\n",LONG_MAX);
	printf("Min size of a signed long:\t%d\n",LONG_MIN);
	printf("Max size of an unsigned char:\t%u\n",UCHAR_MAX);
	printf("Min size of an unsigned char:\t%u\n",CHAR_MIN);
	printf("Max size of a signed char:\t%d\n",CHAR_MAX);
	printf("Min size of a signed char:\t%d\n",CHAR_MIN);

	return 0;
}
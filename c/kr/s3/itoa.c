/*
 * Example function itoa from K&R's ANSI C 2nd edition
 * converts integers into characters (except for some edge cases
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0

/* prototype for atoi */
void itoa(int n, char s[]);
/* prototype for reverse() */
void reverse(char s[]);

int main()
{
	/* create an array to print out */
	char astring[32];
	/* integer to have been converted */
	int input;

	input = -(pow(2,sizeof(int) - 1));
	itoa(input, astring);
	printf("~MAX = %d\n",input);
	printf("%d converted to a string is:\t%s\n",input,astring);
	return 0;
}

/* itoa() found on page 64 */
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0) /* records the sign */
	{
		n = -n; /* make n positive if negative */
	}
	i = 0;
	do
	{
		/* generate the digits in reverse order */
		s[i++] = n % 10 + '0'; /* get the next digit */
		/*
		 * while not stated in the book, this basically takes the value of s[i++]
		 * integer divides by 10, and adds the value of ASCII '0' to the result,
		 * this basically jumps around the ASCII "table" of characters by their integer
		 * value. This vastly simplifies the process of converting the characters into integers and back
		 */
	} while ((n /= 10) > 0); /* delete it */
	/* 
	 * The "delete it" comment was taken from the book,
	 * it works by performing integer division on the value 'n' 
	 * and assigns the result back to 'n'. So long as 'n' is greater than 10, 
	 * the loop reiterates.
	 */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* reverse, as found on page 62 */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

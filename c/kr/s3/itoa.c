/*
 * Example function itoa from K&R's ANSI C 2nd edition
 * converts integers into characters (except for some edge cases
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 

/* prototype for atoi */
void itoa(int n, char s[]);
/* prototype for reverse() */
void reverse(char s[]);

int main()
{
	/* create an array to print out */
	char astring[MAX];
	/* integer to have been converted */
	int input;

	input = ~MAX;
	itoa(input, astring);
	printf("%d converted to a string is:\n%s\n",input,astring);
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
	} while ((n /= 10) > 0); /* delete it */
	if (sign > 0)
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

/*
 * Example function itoa from K&R's ANSI C 2nd edition
 * converts integers into characters (except for some edge cases
 */

#include <stdio.h>
#include <stdlib.h>
#include <reverse.c>

#define MAX 100 

/* prototype for atoi */
void itoa(int n, char s[]);

int main()
{
	/* do things */
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

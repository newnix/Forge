/*
 * Exercise 2-10 from K&R's ANSI C
 * found on page 52
 * Write a function to replace lower()
 * using a ternary expression rather than the equivalent if-else conditions
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"

#define MAX 50

/* create a function prototype */
void lower(char s[]);

int main()
{
	int len;
	char str[MAX - 1]; /* ensure I've got space for a null bit */

	len = get_line(str, MAX);
	lower(str); /* convert to lowercase */
	printf("%s\n",str);
	return 0;
}

void lower(char s[])
{
	int i;
	int lowerdiff;

	lowerdiff = ('a' - 'A'); /* since lower case chars are higher value, use this value to add onto a upper case char */
	for (i = 0; s[i] != 0; i++)
	{
		s[i] = ((s[i] >= 65) && (s[i] <= 'Z')) ? (s[i] + lowerdiff) : s[i];
	}
}

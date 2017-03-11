/* 
 * Example program to show the function reverse()
 * from K&R's ANSI C 2nd edition
 * on page 62
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/get_line.h"

/* max string size I'm willing to deal with */
#define MAX 100

/* create a prototype for reverse() */
void reverse(char s[]);

int main()
{
	/* create a string */
	char input[MAX];
	/* length counter */
	int len;

	len = get_line(input,MAX);
	reverse(input); /* reverses the string in place */
	printf("*input reversed: %s\n",input);

	return 0;
}

void reverse(char s[])
{
	int c, i, j;
	
	/* 
	 * this also uses some interesting notation in the for loop
	 * where the comma operator is used to process two indeces in parallel
	 */
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

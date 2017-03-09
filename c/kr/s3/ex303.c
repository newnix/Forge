/* 
 * Exercise 3-3 in K&R's ANSI C
 * found on page 63
 * meant to write a function called expand(s1,s2)
 * where a given string such as a-z is expanded to the entire alphabet
 * should be able to handle cases like a-z0-9 and -a-z
 * leading or trailing -'s are meant to be taken as literal chars
 * rather than ranges.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"

/* set the input string limit */
#define MAX 100
/* set the output string to be 26x the input size */
#define OMAX (MAX * 26)

/* create expand() prototype */
void expand(char input[], char expand[]);

int main()
{
	char instr[MAX]; /* input from user */
	char ostr[OMAX]; /* output string */
	int len;

	len = get_line(instr,MAX);
	expand(instr,ostr); /* expand the string */
	printf("%s\n",ostr); /* should be fine... or do nothing special */
	return 0;
}

void expand(char input[], char expand[])
{
	/* do magic */
}

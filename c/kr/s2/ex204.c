/* 
 * Exercise 2-4 in K&R's ANSI C 
 * write an alternate version of squeeze()
 * to delete each char in s1 that matches any char in s2
 */

/* 
 * Reference version of squeeze()
 * void squeeze(char s[], int c)
 * {
 * 	int i, j;
 *	for (i = j = 0; s[i] != '\0'; i++)
 *	{
 *		if (s[i] != c)
 *			s[j++] = s[i];
 *	}
 *	s[j] = '\0';
 *}
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"

/* prototype for the new squeeze() */
void squeeze(char s[], int c);

int main()
{
	/* do things */
	char instr[MAX]; /* input string */
	char ostr[MAX]; /* output string */
}

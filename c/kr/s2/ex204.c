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
#include "../headers/grabc.h"

#define MAX 100

/* prototype for the new squeeze() */
void squeeze(char s[], int c);

int main()
{
	/* do things */
	char instr[MAX]; /* input string */
	int len; /* length of the string pulled from the user */
	int del; /* character to delete */
	
	/* get the input from the user */
	while ((len = get_line(instr, MAX)) > 0)
	{
		printf("Enter a char to delete: ");
		del = grabc();
		squeeze(instr, del); /* statically get rid of all 'e' chars */
		printf("Compressed string:\n%s",instr);
	}
	return 0;
}

void squeeze(char s[], int c)
{
	/* we should grab a char from the user and use that to kill the char in instr */
	int i, j;
	
	for (i = j = 0; s[i] != 0; i++)
	{
		if (s[i] != c)
		{
			s[j] = s[i];
			j++;
		}
	}
	s[j] = 0;
}

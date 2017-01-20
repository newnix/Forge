/*
 * Exercise 1-23 of K&R's C
 * page 34
 * Meant to remove comments from a given C file
 */

#define MAX 100000

/* I don't have any experience reading/writing files, so I'll settle for stripping comments from stdin */
#include <stdio.h>
#include "../headers/getline.h"
/* creating a custom version of the getline function to allow it to continue past a single newline */
int getline(char s[], int max);

int main()
{
	int len; /* length of the input string given by the user */
	char instr[MAX]; /* input string pulled from user */
	char lines[MAX]; /* intended to hold up to MAX lines of input from instr */
	int linelen[MAX]; /* separate value to hold the length of each string stored */
	int linenum; /* current line number we're on */

	/* take lines from stdin and strip out comments matching the format used here */
	len = linenum = 0;
	while ((len = getline(instr, MAX)) > 0)
	{
		/* grab all the strings and track them in the array lines[] */
		lines[linenum] = instr; /* store the current line in lines[linenum] */
		linelen[linenum] = len; /* for the same position in linelen[] keep lines[] length */
		linenum++;
	}
	/* so now we need to do things, like looping through the arrays and getting rid of comments */
	return 0;
}

/*
 * Exercise 1-21 from K&R's C
 * page 34
 * Meant to replace runs of spaces with tabs
 */

#include <stdio.h>
#define SPACES 4 /* tabstop value, should there be 4 spaces consecutively, replace them with a single tab */
#define MAX 4000 /* longest string allowed */

int get_line(char s[], int lim); /* pull a line from stdin */
void entabulate(char in[], char out[]); /* add tabs and such */

int main()
{
	/* get the vars in there */
	char instr[MAX]; /* input string */
	char outstr[MAX]; /* output string */
	int len; /* just in case I need to compare lengths of things */

	/* get a string from the user */

/* Exercise 1-18 from K&R's ANSI C
 * meant to delete trailing blank chars
 * as well as lines of all whitespace
 */

#include <stdio.h>
#define MAX 1000 /* I don't want to deal with your crazy strings */

/* forward declarations */
int get_line(char s[], int lim); /* get a line from stdin */
char * condense(char s[]); /* condense whitespace */
void copy(char to[], char from[]); /* copy one string into another */

int main()
{
	/* declare main vars */
	char curstr[MAX], printstr[MAX]; /* char arrays for the copy function */
	int len; /* count the length of a string of input */

	while ((len = get_line(curstr, MAX)) > 0 )
	{
		copy(printstr, condense(curstr));
		printf("%s", printstr);
	}
	/* program ends if it reaches EOF or len == 0 */
	return 0;
}

int get_line(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
	{	
		s[i] = c;
	}
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

/* This is meant to test for adjacent whitespace
 * and skip over repeats
 */
char * condense(char s[])
{
	int a,b,c;
	for (a=0; ((a < MAX) && (s[a] !='\0')); a++)
	{
		printf("s[%d]'s value is: %c\n", a,s[a]);/*	used for testing positions in the string */

		/* s[b] should always be the character after s[a] */
		b = (a + 1);

		if (((s[a] == ' ') || (s[a] == '\t')) && ((s[b] == ' ') || (s[b] == '\t'))) /* test for consectutive whitespace */
		{
			/* we found some whitespace, scan for the next non-whitespace character */
			/* since s[a] is already whitespace, set s[b] to the next non-whitespace character */
		}
	}
	return s;
}

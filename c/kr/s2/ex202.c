/* 
 * Exercise 2-2 on page 42 of K&R's ANSI C
 * meant to create a loop equivalent to the getchar() function
 * from previous exercises without using the && or || operators
 */

#include <stdio.h>
#define slength 1000 /* arbitrary limit because I don't do malloc() yet */

int get_line(char s[], int lim); /* function I'll be redoing with different logic */
int get_line2(char s[], int lim); /* function to be written */
void copy(char from[], char to[]); /* copy strings */

int main()
{
	/* declaring main vars */
	char instring[slength], outstring[slength]; /* input string and output string */

	get_line2(instring, slength); /* get a line of input from the user */
	copy(instring, outstring); /* copy the string to burn some cpu cycles */
	printf("%s",outstring); /* print the string */

	return 0; /* because I don't catch exceptions either */
}

void copy(char from[], char to[])
{
	int i; /* value to step through the char arrays */
	i = 0; /* make sure to start from the beginning */
	while ((to[i] = from[i]) != '\0')
		++i;
}

/* this in the function to be replaced */
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

/* this is the attempt to make it work without && or || */
int get_line2(char s[], int lim)
{
	int c,i;
	c = i = 0; /* initialize to 0 */
	while (i < lim - 1)
	{
		c = getchar();
		if (c != EOF) /* no EOF allowed */
		{
			if (c != '\n') /* newline means new string */
			{
				s[i] = c;
			}
			else if (c == '\n')
			{
				s[i] = c;
				s[i+1] = '\0';
				return i; /* this should kill the loop and return the necessary value */
			}
		else if (c == EOF)
		{
			/* we just hit the EOF, terminate the loop */
			s[i] = '\0'; /* because strings are supposed to be null-terminated */
			return i;
		}
		}

	} ++i;

	s[i+1] = '\0'; 
	return i;
}

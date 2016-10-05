/* begin section 1.9 
 * character arrays
 * this version is for exercise 1-16
 * instead of printing the longest line, this is 
 * meant to count the characters in a line and print the line itself
 */

/* pseudocode for this program */

/*
 * while (there's another line)
 * 	if (input is not EOF)
 * 	{
 * 		determine the length;
 * 		save the length
 * 	}
 * print the length of the line
 * print the line itself
 */


#include <stdio.h>
#define MAXLINE 1000 /* max input line size */

int get_line(char s[], int lim); /* get_line instead of get_line, as get_line is already defined in glibc */
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
	int len, str;	/* current line length */
	char line[MAXLINE]; /* current input line */
	char longest[MAXLINE];	/* print this line */

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		str = len;
		
		/* moved into while() loop to try to continue execution */
		copy(longest, line);
		if (str > 0)
		{
			/* print the length */
			printf("\nInput was %d characters long.\n", (str - 1));
			printf("%s", longest);
		}
		else
		{
			printf("This really shouldn't be seen...\nGoodbye.\n");
		}
	}
	/* the above loop ends when an empty string is provided from stdin */
	return 0;
}

/* get_line: read a line into s, return length */
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

/* copy: copy 'from' into 'to'; assume that 'to' is big enough */
void copy(char to[], char from[])
{
	int i;

	i = 0; 
	while ((to[i] = from[i]) != '\0')
		++i;
}

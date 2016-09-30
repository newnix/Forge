/* begin section 1.9 
 * character arrays
 */

/* pseudocode for this program */
/*
 * while (there's another line)
 * 	if (it's longer than the last line)
 * 	{
 * 		save it;
 * 		save its length;
 * 	}
 * print longest line.
 */


#include <stdio.h>
#define MAXLINE 1000 /* max input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
main()
{
	int len;	/* current line length */
	int max;	/* max length so far */
	char line[MAXLINE]; /* current input line */
	char longest[MAXLINE];	/* longest line saved here */

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	if (max > 0)
	{
		printf("%s", longest);
		return 0;
	}
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
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

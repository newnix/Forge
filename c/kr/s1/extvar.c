/*
 * Example program rewriting the "longest line"
 * program from K&R where we use external variables instead
 * of local variables. 
 * p.32
 */

#include <stdio.h>

#define MAX 1000 /* this is the most chars I want to use */

int max;	/* max line length so far */
char line[MAX];	/* current input line */
char longest[MAX];	/* longest line of input */

/* forward declaration */
int getline(void);
void copy(void);

/* print longest input line; external vars */
int main()
{
	int len;
	extern int max;	/* explicitly reference the external var */
	extern char longest[];

	max = 0;
	while ((len = getline()) > 0)
	{
		if (len > max)
		{
			max = len;
			copy();
		}
	}

	if (max > 0)	/* there's a line */
		printf("%s",longest);
	return 0;
}

/* getline, still not gnu getline */
/* does utilize external vars tho */
int getline(void)
{
	int c, i;
	extern char line[];

	for (i = 0; i < MAX - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n')
	{
		line [i] = c;
		++i;
	}
	line [i] = '\0';
	return i;
}

/* copy with external vars */
void copy(void)
{
	int i;
	extern char line[], longest[];

	i = 0;
	while ((longest[i] = line[i]) != '\0')
		++i;
}

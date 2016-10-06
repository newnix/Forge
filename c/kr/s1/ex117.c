/* exercise 1-17 from K&R's ANSI C 
 * meant to print any lines from stdin
 * that are greater than 80 chars long
 */

/* pseudocode for this objective:
 * if (there's a line from stdin)
 * {
 * 	determine the length;
 * 	if (length > 80)
 * 	{
 * 		print line;
 * 	}
 * 	else if (length > 0)
 * 	{
 * 		reset the counter(s);
 * 	}
 * 	else
 * 	{
 * 		terminate;
 * 	}
 * }
 */

#include <stdio.h>
#define MIN 80 /* the minimum size to print */
#define MAX 1000 /* max input size I'm willing to allow */

/* forward declarations, functions will be defined later */
int get_line(char s[], int lim); /* again using get_line instead of getline */
void copy(char to[], char from[]); /* copy one char array into another */

int main()
{
	/* declare the vars needed, such as the char arrays to be tested/saved */
	int len, str; 	/* current length */
	char curlen[MAX], printlen[MAX]; /* char arrays for the lening comparisons */
	
	while ((len = get_line(curlen, MAX)) > 0)
	{
		str = len;
		copy(printlen, curlen);
		if (str >= MIN)
		{
			/* copy the line into printlen */
			printf("\nInput was %d characters over the minimum.\n",(len - 80));
			printf("%s",printlen);
		}
		else
			printf("\n");
	}
	return 0;
}

/* get a line from stdin, returns the length */
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

/* copy: copies the 'from' lening into the 'to' lening */
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

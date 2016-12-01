/*
 * Exercise 1-20 in K&R's C
 * page 34
 * meant to replace tabs with the relevant number of spaces
 * manipulates strings pulled from stdin rather than a file
 */

#include <stdio.h>
#define SPACES 4 /* how many spaces should a tab be replaced with */
#define MAX 4000 /* longest string allowed */

int get_line(char s[], int lim); /* pull a line from stdin*/
void expand_tab(char in[], char out[]); /* used to swap tabs for spaces using the SPACES value */
void copy(char to[], char from[]); /* used to manipulate strings with more flexibility, may not really be needed in this practice program */

int main()
{
	/* first things first, let's get some vars */
	char instr[MAX]; /* input string */
	char tabstr[MAX]; /* tab string */
	int len; /* hold the length of the string from stdin, in case keeping such a thing becomes useful */

	/* actually get the input from the user */
	while ((len = get_line(instr, MAX)) > 0)
	{
		/* expand the tabs */
		expand_tab(instr, tabstr);
		/* there probably needs to be a check made to count the tabs and determine how
		 * much extra space in the array needs to be available to expand all the tabs,
		 * and throw an error should the projected length of tabstr not be small enough to fit with MAX
		 */
		printf("%s\n",instr);
		printf("%s\n",tabstr);
	}
	return 0;
}

int get_line(char s[], int lim)
{
	int c, i;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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

void expand_tab(char in[], char out[])
{
	/* use a for loop to find each instance of a '\t',
	 * then pause inside of one loop to substitute 4 spaces instead,
	 * otherwise, the content of in[] should not be modified.
	 */
	int a,b,c; /* counters for each string */

	a = b = c = 0; 

	for (a = 0; in[a] != EOF && in[a] != '\0'; a++)
	{
		printf("in[%d] = %c\n",a,in[a]);

		if (in[a] != '\t')
		{
			out[c] = in[a];
			c++;
		}
		else
		{
			/* ensure b == 0 so we can effectively use the following loop */
			for (b = 0; b < SPACES; b++)
			{
				out[c] = ' ';
				printf("out[%d] = %c\n",c,out[c]);
				c++;
			}
			
		}
	}
	c++;
	out[c] = '\0';

	for (a = 0; out[a] != EOF && out[a] != '\0'; a++)
	{
		printf("out[%d] = %c\n",a,out[a]);
	}
}

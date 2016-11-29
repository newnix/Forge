/* Exercise 1-18 from K&R's ANSI C
 * meant to delete trailing blank chars
 * as well as lines of all whitespace
 */

#include <stdio.h>
#define MAX 1000 /* I don't want to deal with your crazy strings */

/* forward declarations */
int get_line(char s[], int lim); /* get a line from stdin */
void condense(char s[], char c[]); /* condense whitespace */
void copy(char to[], char from[]); /* copy one string into another */

int main()
{
	/* declare main vars */
	char curstr[MAX], printstr[MAX], constr[MAX]; /* char arrays for the copy function */
	int len; /* count the length of a string of input */

	while ((len = get_line(curstr, MAX)) > 0 )
	{
		condense(curstr,constr);
		copy(printstr,constr);
		printf("%s\n", printstr);
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
 *
 * Lunch break is not long enough to look at reworking this function right now, but 
 * I'm thinking this should be changed to type void, and run two concurrent loops
 * one to write from the string collected by stdin, one to strip out excess whitespace when encountered.
 * It's not as efficient as filtering the input directly, but I'm not ready to takle that issue just yet.
 */
 
void condense(char s[], char c[])
{
	/* declare two ints so we can track the position in two separate strings */
	int a,b; /* a will track s[], b will track c[] */
	a = b = 0;
	for (a = 0; a <= MAX && s[a] != '\0'; a++)
	{
		/* help with debugging, show me each char value in the string */
		printf("s[%d] = %c\n",a,s[a]);
		
		/* search for whitespace */
		if ((s[a] == ' ' || s[a] == '\t') && (s[a+1] == ' ' || s[a+1] == '\t'))
		{

			/* we have whitespace, start looking for next non-whitespace char */
			do
			{
				/* help with debugging */
				printf("s[%d] = %c\n",a,s[a]);
				a++;
			}while (s[a] == ' ' || s[a] == '\t');

			c[b] = s[a];
		}
		else
		{
			c[b] = s[a];
		}
		b++;
	}
	/* set the last byte in the array as NULL */
	c[b] = '\0';
}

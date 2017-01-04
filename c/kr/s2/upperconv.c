/* test program to convert the values in a given string to their upper case equivalent */
/* essentially a custom upper() function */
#include <stdio.h>

#define MAX 100 /* max string length */

char upper(int c); /* prototype, since the int value translates directly to a char */
int get_line(char s[], int lim);

int main()
{
	/* first get a line of input */
	char instr[MAX];
	int len,i;

	while ((len = get_line(instr, MAX)) > 0)
	{
		/* convert to upper */
		for (i = 0; i < len; ++i)
		{
			instr[i] = upper(instr[i]);
	/*		printf("%c\n",instr[i]); used to help visualize the conversion */
		}
		/* print the resulting string */
		printf("%s\n",instr);
	}

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

char upper(int c)
{
	int upperdif; /* difference between lower and upper values */
	upperdif = (97 - 65); /* set the diff to the difference between upper and lower 'a' */

	if ((c <= 122 ) && (c >= 97)) /* between lower 'z' and 'a' */
		 c = (c - upperdif);
	
	return c;
}

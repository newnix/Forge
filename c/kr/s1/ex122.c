/*
 * Exercise 1-22 on K&R's C
 * page 34
 * Meant to act as rudimentary word-wrap
 */

#include <stdio.h>
/* wrap is the minimum number of characters at which to wrap words */
#define WRAP 70
#define MAX 1000 

/* forward declaration of some functions */
int getline(char s[], int max);
void wrapit(char s[], int len, int wlen, char w[]);

int main()
{
	int len; /* length of the current string */
	char instr[MAX]; /* the input string */
	char wstr[MAX * 2]; /* the wrapped string, should be long enough to catch any string passed to instr */
	len = 0;

	while ((len = getline(instr, MAX)) > 0)
	{
		/* wrap instr as best as possible */
		wrapit(instr, len, WRAP, wstr);
		printf("%s\n", wstr);
		/* let the user know that they can either type more or hit ^D */
		printf("\nEither enter more text to pass through word-wrap or hit ^D to exit:\n");
	}
	return 0;
}

int getline(char s[], int max)
{
	int c, i;

	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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

void wrapit(char s[], int len, int wlen, char w[])
{
	/* wrap the string as close to wlen as possible */
	int wrap; /* are we currently trying to wrap the string? psuedo-boolean for ansi c */
	int i; /* current spot in the input string */
	int wi; /* current spot in the wrapped string */

	for (wrap = wi = i = 0; i < len; ++i)
	{
		if (wrap >= WRAP)
		{
			w[wi] = '\n';
			wi++;
			w[wi] = s[i]; /* this will be a mostly 1-1 mapping */
			wi++; /* ensure that wi is keeping up with i */
			wrap = 0; /* reset the counter */
		}
		else
		{
			w[wi] = s[i]; /* this will be a mostly 1-1 mapping */
			wi++; /* ensure that wi is keeping up with i */
			wrap++;
		}
	}
}

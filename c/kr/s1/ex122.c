/*
 * Exercise 1-22 on K&R's C
 * page 34
 * Meant to act as rudimentary word-wrap
 */

/* wrap is the minimum number of characters at which to wrap words */
#define wrap 70
#define max 1000 /* max string length */
#include <stdio.h>

/* forward declaration of some functions */
int getline(char s[], int max);
void wrapit(char s[], int len, int wlen, char w[]);

int main()
{
	int len; /* length of the current string */
	char instr[max]; /* the input string */
	char wstr[max * 2]; /* the wrapped string, should be long enough to catch any string passed to instr */
	len = 0;

	while ((len = getline(instr, max)) > 0)
	{
		/* wrap instr as best as possible */
		wrapit(instr, len, wrap, wstr);
		printf("%s\n", wrstr);
		/* let the user know that they can either type more or hit ^D */
		printf("\nEither enter more text to pass through word-wrap or hit ^D to exit:\n");
	}
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
	bool wrap; /* are we currently trying to wrap the string? */
	int i; /* current spot in the input string */
	int wi; /* current spot in the wrapped string */
}

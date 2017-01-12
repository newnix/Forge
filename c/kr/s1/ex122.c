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
void wrapit(char s[], int wlen);

int main()
{
 	/* do stuff */
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

void wrapit(char s[], int wlen)
{
	/* wrap the string as close to wlen as possible */
}

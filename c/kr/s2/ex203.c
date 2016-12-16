/* 
 * Exercise 2-3 on page 46 of K&R
 * get a string of input from the user,
 * then convert it from hex to an integer
 */

#define max 100 /* because wtf are you thinking if you give me more than than in hex?? */

/* htoi() -> hex to int */
/* This should return an int from a given string */
int htoi(char s[]);
int get_line(char s[], int lim);

#include <stdio.h>

int main()
{
	char hexin[max]; /* string containing the hex value */
	int lim = max; /* string limits */
	int hex;	/* integer value of the hex string */
	int len;
	
	printf("Enter a hexadecimal value, with or without the leading \"0x\":\n");
	
	while ((len = getline(hexin, max)) > 0)
	{
		/* not sure what to put here yet */
		printf("%s\n",hexin);
	}

	return 0;
}

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

int htoi(char s[])
{
	/* will have to check the string for valid hex values */

	/* after verifying it's good, convert to an integer value */
	/* ....somehow... */
}

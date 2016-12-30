/* 
 * Exercise 2-3 on page 46 of K&R
 * get a string of input from the user,
 * then convert it from hex to an integer
 */

#define max 20 /* because wtf are you thinking if you give me more than than in hex?? */

/* htoi() -> hex to int */
/* This should return an int from a given string */
int htoi(char s[], int len);
int get_line(char s[], int lim);
int hexcon(char h[], int len); /* essentially a switch statement with hex values */

#include <stdio.h>

int main()
{
	char hexin[max]; /* string containing the hex value */
	int lim = max; /* string limits */
	int hex;	/* integer value of the hex string */
	int len;
	
	printf("Enter a hexadecimal value, with or without the leading \"0x\":\n");
	
	while ((len = get_line(hexin, max)) > 0)
	{
		/* not sure what to put here yet */
		printf("%s\n",hexin);
		printf("%u\n",hexin); /* this appears to be doing some interesting conversions on the string values, not sure exactly what */
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

int htoi(char s[], int len)
{
	/* will have to check the string for valid hex values */
	int i; /* used to step through the string, checking for invalid values */
	int h; /* holds the value of hex[] so we have a valid hex string */
	char hex[max]; /* verified hex string */

	/* switch for the possibility of a preceeding '0x' */
	if ((s[0] == '0') && ((s[1] == 'x') || s[1] == 'X'))
	{
		/* start i at 2 */
		for (i = 2; i < max -1; i++)
		{
			/* test for the int values for various valid characters */
			if ((s[i] >= 'A' && s[i] <= 'F') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >='0' && s[i] <= '9'))
			{
				/* collect the values so we can turn them into an int later */
				hex[h] = s[i]; 
				h++;
			}
		}
	}
	else
	{
			/* start i at 0 */
		for (i = 0; i < max -1; i++)
		{
			/* test for the int values for various valid characters */
			if ((s[i] >= 'A' && s[i] <= 'F') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >='0' && s[i] <= '9'))
			{
				/* collect the values so we can turn them into an int later */
				hex[h] = s[i];
				h++;
			}
		}
	/* after verifying it's good, convert to an integer value */
	/* ....somehow... */
	}
	return 0;
}

/*
 * The general formula for converting a hex value to an int is (<value> x 16^n-1)+(<value-1> x 16^n-2)
 * and so on. The values range from 0-15 (int) and 0-9,A-F (hex).
 * With the current setup, the power limit's 99, this is likely going to be excessive.
 * I think I'll lower it to something more sensible like 20.
 */
int hexcon(h[], int len)
{
	/* here we convert things to an int */
	/* This will simply hold the decimal values of the hex characters */
	/*
	 * 0 = 0    8 = 8
	 * 1 = 1    9 = 9
	 * 2 = 2    A = 10
	 * 3 = 3    B = 11
	 * 4 = 4    C = 12
	 * 5 = 5    D = 13
	 * 6 = 6    E = 14
	 * 7 = 7    F = 15
   */
  
  int i; /* for running through the string */

  /* calculate the values independantly, then return the calculated int value */

	for (i = 0; i < len; i++)
	{
		/* determine the value of each character in the string */
		/* should be a switch/case block, since we're basically getting chars to look at */
	}
}

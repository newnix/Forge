#ifndef CHARCONV_H
#define CHARCONV_H
/*
 * I guess this is essentially becoming a prototype library.
 * which is why the name changed from upper.h to charconv.h,
 * Any time I learn a new way to manipulate characters in a string
 * I'll add a function to this file, so it can be reused and tweaked as needed
 */
#include <string.h>
/* if tabstop hasn't been defined, make it 4 */
#ifndef TABSTOP
#define TABSTOP 4
#endif

/* convert characters to uppercase */
/* this version only works on one char at a time */
char upperc(char c)
{
	int upperdiff; /* difference between 'a' and 'A' */
	upperdiff = (97 - 65);
	/* checks if the value is between 'z' and 'a', then adjust if needed */
	c = ((c <= 'z') && (c >= 'a')) ? (c - upperdiff) : c;
	return c;
}

/* converts all chars in a string to uppercase */
void upper(char s[])
{
	int i;
	int upperdiff;
	upperdiff = (97 - 65);

	for (i = 0; s[i] != 0; i++)
	{
		/* turns out ternary is pretty simple and fun */
		s[i] = ((s[i] >= 'a') && (s[i] <= 'z')) ? (s[i] - upperdiff) : s[i];
	}
}

/* converts all chars in a string to lowercase */
void lower(char s[])
{
	int i;
	int upperdiff;
	upperdiff = (97 - 65);

	for (i = 0; s[i] != 0; i++)
	{
		s[i] = ((s[i] >= 'A') && (s[i] <= 'Z')) ? (s[i] + upperdiff) : s[i];
	}
}

/* convert a single char to lowercase */
char lowerc(char c)
{
	int upperdiff;
	upperdiff = (97 - 65);

	c = ((c <= 'Z') && (c >= 'A')) ? (c + upperdiff) : c;
	return c;
}

/* 
 * Yanked from ex302.c
 * may not actually be useful in the real world
 */
void escape(char to[], char from[])
{
  /* 
   * should be a for loop ending at the null terminator,
   * case statement should escape after modifying the string and updating the index
   * afterwards, the string should be appended a null terminator so it can be printed properly
   */

	int i, j; /* indexes for each string */

	i = j = 0;

	/* now we step through the strings */
	for (i = 0; from[i] != 0; i++) /* '\0' is the same as 0 */
	{
		switch (from[i]) /* make decisions based off the value of t[i] */
		{
			case '\t':
				/* found a tab, replace with literal \t */
				to[j] = '\\';
				j++;
				to[j] = 't';
				break;
			case '\n':
				/* found a newline, replace with literal \n */
				to[j] = '\\';
				j++; 
				to[j] = 'n';
				break;
			default:
				/* nothing special, just assign the value directly to the new string */
				to[j] = from[i]; /* can't use i as the index for both, as they may not be the same value at this point */
				break;
		}
		j++; /* increment every time we move to a new index in t[] */
	}
	to[j + 1] = 0; /* make sure we have a NULL terminator */
}

/*
 * reversal function, reverses a string in place
 */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
#endif

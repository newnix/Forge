/*
 * Exercise 3-2 from K&R's ANSI C 
 * found on page 60
 * Meant to create a function called escape(s,t)
 * which converts the newline and tab characters to their escape sequences
 * and vice-versa while copying string t to s using a switch statement
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"
/* this is the maximum input string I'm wiling to take from the user */
#define MAX 100
/* tabs -> spaces conversion */
#define TABSTOP 4
/* create a function prototype */
void escape(char s[], char t[]);

int main()
{
  /* create a couple of ints */
  int len, tmax;
  tmax = MAX * TABSTOP; /* just in case it's all tabs */
  /* create a couple of strings */
  char instr[MAX]; /* input string from the user */
  char trstr[tmax]; /* should be 4x the size of instr, jic it's all tabs */

  len = get_line(instr,MAX); /* capture a line of input, though it looks like this could be replaced with scanf() */
	if (len > 0) { 
		printf("Captured:\n%s\n",instr);
		escape(trstr,instr); /*essentially transpose the string into the other */
		printf("Transposed:\n%s\n",trstr); /* if this doesn't work properly, it'll likely just be printing garbage */
	}

  return 0;
}

void escape(char s[], char t[])
{
  /* 
   * should be a for loop ending at the null terminator,
   * case statement should escape after modifying the string and updating the index
   * afterwards, the string should be appended a null terminator so it can be printed properly
   */

	int i, j; /* indexes for each string */

	i = j = 0;

	/* now we step through the strings */
	for (i = 0; t[i] != 0; i++) /* '\0' is the same as 0 */
	{
		switch (t[i]) /* make decisions based off the value of t[i] */
		{
			case '\t':
				/* found a tab, replace with literal \t */
				s[j] = '\\';
				j++;
				s[j] = 't';
				break;
			case '\n':
				/* found a newline, replace with literal \n */
				s[j] = '\\';
				j++; 
				s[j] = 'n';
				break;
			default:
				/* nothing special, just assign the value directly to the new string */
				s[j] = t[i]; /* can't use i as the index for both, as they may not be the same value at this point */
				break;
		}
		j++; /* increment every time we move to a new index in t[] */
	}
	s[j + 1] = 0; /* make sure we have a NULL terminator */
}

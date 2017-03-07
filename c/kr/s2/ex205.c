/*
 * Exercize 2-5 from K&R's ANSI C
 * write a function called any()
 * this function should return the first location 
 * in string s1 where it matches any char in s2
 * should return -1 if no matches are found
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"
#include "../headers/grabc.h"
#include "../headers/upper.h"

#define MAX 100

int any(char s1[], char s2[]);

int main()
{
	char str1[MAX],str2[MAX];
	int len1,len2;
	int idex;
	char again; /* does the user want to run the program again? */
	/* grab two lines with indexes, then compare them */
	/* perhaps nesting while loops? else would need to find a way to ensure both strings have been initialized and aren't NULL */
	
	again = 'N'; /* default to not running the loop again */

	do
	{
		/* from here we compare the strings, and possibly reset them as well */
		len1 = get_line(str1,MAX);
		len2 = get_line(str2,MAX);
		idex = any(str1, str2);

		/* if we get a number <= 0, we have a problem, bail out */
		if (idex <= 0)
		{
			return 500;
		}

		printf("Any() returned: %d\n", idex);
		printf("\nRun again? [y/n]\n");
		again = grabc();
	}while (upper(again) != 'N');
	return 0;
}

int any(char s1[], char s2[])
{
	/* compare the strings! */
	int i, j; /* indices for both strings */

	for (i = 0; s1[i] != 0; i++)
	{
		for (j = 0; s2[j] != 0; j++)
		{
			/* run through both strings comparing them */
			if (s1[i] == s2[j])
			{
				return i; /* matching value, return index */
			}
		}
	}
	return -1; /* no matching index found */
}

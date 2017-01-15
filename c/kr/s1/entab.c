/*
 * Exercise 1-21 from K&R's C
 * page 34
 * Meant to replace runs of spaces with tabs
 */

#include <stdio.h>
#include "../headers/getline.h"
#define SPACES 4 /* tabstop value, should there be 4 spaces consecutively, replace them with a single tab */
#define MAX 4000 /* longest string allowed */

void entabulate(char in[], int len, char out[]); /* add tabs and such */

int main()
{
	/* get the vars in there */
	char instr[MAX]; /* input string */
	char outstr[MAX]; /* output string */
	int len; /* just in case I need to compare lengths of things */
	int dbg; /* debugging buddy */

	/* get a string from the user */
	while ((len = getline(instr, MAX)) > 0)
	{
		for (dbg = 0; dbg < len; ++dbg)
		{
			printf("instr[%d] = %d,%c\n",dbg,instr[dbg],instr[dbg]);
		}
		entabulate(instr, len, outstr);
		for (dbg = 0; dbg < len; ++dbg)
		{
			printf("outstr[%d] = %d,%c\n",dbg,outstr[dbg],outstr[dbg]);
		}
		printf("%s\n",outstr);
	}
	return 0;
}

void entabulate(char in[], int len, char out[])
{
	/* add tabs! */
	int i; /* step through the input string */
	int t; /* step through the output string */

	for (t = i = 0; i < len; ++i)
	{
		if (in[i] == 32 && in[i+1] == 32 && in[i+2] == 32 && in[i+3] == 32)
		{
			out[t] = 9;
			i++; /* jump to the next non-space char (hopefully) */
			t++;
		}
		else
		{
			out[t] = in[i];
			i++;
			t++;
		}
	}
	if (out[t] != '\0')
	{
		out[t+1] = '\0';
	}
}

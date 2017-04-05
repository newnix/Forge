/*
 * Exercise 4-1 from K&R's ANSI C 2nd Edition
 * page 71, meant to create a function called strrindex(s, t),
 * which returns the rightmost occurence of t in s, or -1 if there isn't one
 * This should essentially be a modified version of the example grep 
 * program, but with a modified search function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* needed for upperc() */
#include "../headers/charconv.h"

/* prototype strrindex */
int strrindex(char *s, char*t);

/* 
 * create a static buffer to hold an input string
 * because dynamic allocation is dificult
 */
#define MAXLEN 1024

int main(void) {
	char input[MAXLEN]; /* the max input size I'm willing to sift through */
	char * sstr; /* the substring to scan for */
	char * again; /* continue looping? */
	int found = 0; /* the number of matched substrings */
	int idex = 0; /* the index of the match */

	/* allocate memory for the search string */
	if ((sstr = malloc(1024 * sizeof(char))) == NULL) { 
		printf("ERROR: COULDN'T ALLOCATE MEMORY FOR *sstr\n");
		return 2;
	}
	/* allocate memory for the loop continuation */
	if ((again = malloc(sizeof(char))) == NULL) { 
		printf("ERROR: COULDN'T ALLOCATE MEMORY FOR *again");
		return 2;
	}

	/* printf("Enter a string to search through: "); */
	for (;;) {
		printf("Enter a string to search through: ");
		/* for some reason, https://wpollock.com/CPlus/PrintfRef.htm was the first reference to this format string */
		scanf("%[^\n]",input); /* the format string %[^\n] will read up to the next newline, and assign it to input */
		/* scanf() is apparently pretty finicky with user input */
		printf("Enter substring to match against: ");
		scanf(" %s",sstr);
		/* run a rudimentary grep with the strings */
		if ((idex = strrindex(input, sstr)) >= 0) {
			printf("Match found at index %d\n", idex);
			found++;
		}
		printf("\nWould you like to run again? [y/N] ");
		scanf(" %c",again);
		if (upperc(*again) != 'Y') {
			return found;
		}
		else {
			bzero(sstr,strlen(sstr)); /* zero out the search string */
		}
	} 
}

int strrindex(char *s, char *t) {
	/* scan the lines */
	int i, j, k, rmatch;

	/* initialie rmatch */
	rmatch = -5;

	for (i = 0; s[i] != 0; i++) {
		for (j = i, k = 0; t[k] != 0 && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == 0)
			rmatch = i; /* found a match, set rmatch to the index */
	}
	if (rmatch >= 0)
		return rmatch; /* assuming it's been otherwise set, return rmatch */
	else
		return -1;
}

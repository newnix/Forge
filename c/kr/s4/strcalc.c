/*
 * This is meant to be a string based calculator
 * as stated in K&R's ANSI C 2nd edition, on page 72
 * this particular implementation would barely be sufficient 
 * for balancing a checkbook, but it should be fun to work on
 */

#include <stdio.h>
#include <stdlib.h>

/* maximum size of input */
#define MAX 1024

/* create a function to determine what class characters are */
void  charclass(char * s);
/* and a function for the math, similar to atof() */
double compute(char *s);
/* this function verifies the mathematical string is valid */
void verify(char *s);

int main(void) {
	/* do some magic things */
	return bored;
}

void charclass(char *s, int slen) {
/* 
 * get the values of each character type in the given string
 * then sort them into different types: alpha, num, op, other
 * and add the index to the appropriate array
 * then, build new strings to pass off to other functions
 */
	
	/* the only thing we care about are the characters that can be used for basic math */
	char opstr[MAX]; /* drop the numbers and operators into this string */
	int i,j; /* string iterators */

	for (i = j = 0; s[i] != 0; i++) { 
		/* test each char in the string */
		if (s[i] >= 48 && s[i] <= 57) {
			/* The character is a number */
			opstr[j] = s[i];
			j++;
		}
		else if (s[i] >= 32 && s[i] <= 47) { 
			switch (s[i]) {
				case (42):
					opstr[j] = s[i];
					j++;
					break;
				case (43):
					opstr[j] = s[i];
					j++;
					break;
				case (47):
					opstr[j] = s[i];
					j++;
					break;
				case (45):
					opstr[j] = s[i];
					j++;
					break;
				case (32): 
					opstr[j] = s[i];
					j++;
					break;
				default:
					break;
			}
		}
	}
	verify(opstr);
}

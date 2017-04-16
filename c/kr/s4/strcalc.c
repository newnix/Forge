/*
 * This is meant to be a string based calculator
 * as stated in K&R's ANSI C 2nd edition, on page 72
 * this particular implementation would barely be sufficient 
 * for balancing a checkbook, but it should be fun to work on
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* maximum size of input */
#define MAX 1024

/* create a function to determine what class characters are */
void  charclass(char * s);
/* and a function for the math, similar to atof() */
double compute(char *s);
/* this function verifies the mathematical string is valid */
void verify(char *s);
/* make sure that the order of operations is correct, just to be safe */
void pemdas(char *s);
/* and ensure we don't let something stupid happen like dividing by 0 */
void div0(char *s);

int main(void) {
	char input[MAX];

	printf("Please enter a string to evaluate mathematically: ");
	scanf("%[^\n]", input);
	charclass(input);
	/* do some magic things */
	return 0;
}

void charclass(char *s) {
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
				case (42): /* this is a '*' */
					opstr[j] = s[i];
					j++;
					break;
				case (43): /* this is a '+' */
					opstr[j] = s[i];
					j++;
					break;
				case (47): /* this is a '/' */
					opstr[j] = s[i];
					j++;
					break;
				case (45): /* this is a '-' */
					opstr[j] = s[i];
					j++;
					break;
				case (32): /* this is a space */
					opstr[j] = s[i];
					j++;
					break;
				case (46): /* this is a '.' */
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

void verify(char * s) {
/* verify that the string entered can be evaluated mathematically */
	/* set up some integer indices */
	int i, j, len;
	
	printf("%s\n",s); /* this is just to help visualize the current state of the string */

	len = strnlen(s, len);

	for (i = 0; i < len; i++) {
		/* remove consecutive runs of spaces */
		if (s[i] = 32 && s[i+1] = 32) { 
			/* found at least two spaces */
			/* scan for next non-whitespace character */
			condense(s, i, j, len);
			/* this likely wouldn't be the a terribly efficient solution, but it should give the right results */
		}
	}
}

void condense(char * string, int start, int stop, int length) {
/* shrink the string and recalculate the length */
	int i; /* string iterator */
	char c; /* placeholder */

	for (i = 0; i < len; i++) {
		/* do some things */
	}
}	

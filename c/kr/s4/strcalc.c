/*
 * This is meant to be a string based calculator
 * as stated in K&R's ANSI C 2nd edition, on page 72
 * this particular implementation would barely be sufficient 
 * for balancing a checkbook, but it should be fun to work on
 */

#include <stdio.h>
#include <stdlib.h>

/* create a function to determine what class characters are */
void  charclass(char * s);
/* and a function for the math, similar to atof() */
double compute(char *s);
/* and one to actually isolate the arithmetic expressions, no accounting for parens/braces/brackets */
void isolateMath(char *s);

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
	
	/* create int arrays for the assignment of character indexes */
	int * alpha;
	int * num;
	int * op;
	int * other;


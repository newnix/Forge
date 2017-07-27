/* 
 * This is meant to extend the basic function atoi(char s[])
 * to handle scientific notation. (eg 3.1e8 = 3.1x10^8)
 * allowing either 'e' or 'E' to be used with an optionally
 * signed integer as the exponent
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "../headers/charconv.h"

#define MAXSTR 1024

/* prototype of the conversion function */
double sci_atof(char *s);
/* prototype to determine if we run the program again */
int go_again(char c);
/* prototype for determining the value of the power */
double setpow(char *s, int i, int powsize);
/* build the base expression */
double buildbase(char c);
/* calculate the value of the base expression */
double convbase(char *base); 

int main(void) {

	/* create an array to hold the largest feasible amount of data from stdin */
	char sci[MAXSTR];
	/* run the conversion again? */
	char again;
	/* create a placeholder for the resulting value */
	double sciflt;
	/* let the user know what's going on */
	again = '\0';
	do {
		/* first, ensure we have an empty buffer */
		memset(sci,0,1024);
		printf("Please enter a string, in scientific notation to convert to a numeric value: ");
		/* get everything up to the newline */
		scanf("%[^\n]",sci);
		/* run the conversion */
		sciflt = sci_atof(sci);
		printf("%s converted to a floating point is %f\n", sci,sciflt);
		printf("Would you like to go again? [y/N] ");
		scanf("%[^\n]",again);
	} while (go_again(again));
	return 0;
}

/* returns 1 if wanting to go again, 0 otherwise */
int
go_again(char c) {
	switch (upperc(c)) {
		case 'Y':
			return 1;
			break;
		case 'N':
			return 0;
			break;
		default:
			return 0;
			break;
	}
}

/* return the value of the given string as a floating point number */
double
sci_atof(char *s) {
	/* magic things */
	int idex, powsize; /* intex of the char array */
	double base, powr;
	base = powr = 0;

	/* run through the string to find a usable expression */
	for (idex = 0; s[idex] != 0; idex++) {
	  if (isnum(s[idex])) {
		}
		else if (upperc(s[idex]) == 'E') {
		/* found the power exp; break this loop to calculate the second part */
			powsize = strlen(s) - idex;
			powr = setpow(s,idex,powsize);
			break;
		}
	}
	return (pow(base,powr));
}

/* get the power that the previous expression's being raised to */
double 
setpow(char *power, int index, int powsize) {
	int j; /* create a counter so we can verify the correct size of the power value */
	int rpow; 
	double curpow;
	j = 0; /* ensure that the expression gets raised to the right power */
	curpow = 0;
	/* this should be a number, usually an integer, so we'll not process a '.' or the following numbers */
	for (j; (power[index+j] != 0 && power[index+j] != '.'); j++) {
		/* get the integer representation of whatever value is being passed */
		/* but ensure we don't try doing anything supid like trying to parse a non-digit char */
		rpow=pow(10,powsize-j);
		curpow += isdigit(power[i]) ? ((power[i] - 48) * rpow) : 0; /* if we have a digit, add it to the power value */
	}
	return curpow;
}

/* build the base value of the expression (everything before the exponent) */
double
buildbase(char baseval, int power, int powerval) {
	double baseconv; /* conversion of char to double */
	baseconv = isdigit(baseval) ? (baseval - 48) : 0; /* assuming it's a digit, we take the numeric value of it */
	/* at this point, the value should be computed */
	return baseconv;
}

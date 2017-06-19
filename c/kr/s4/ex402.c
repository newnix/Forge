/* 
 * This is meant to extend the basic function atoi(char s[])
 * to handle scientific notation. (eg 3.1e8 = 3.1x10^8)
 * allowing either 'e' or 'E' to be used with an optionally
 * signed integer as the exponent
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 1024

/* prototype of the conversion function */
double sci_atof(char *s);
/* prototype to determine if we run the program again */
int go_again(char c);

int main(void) {

	/* create an array to hold the largest feasible amount of data from stdin */
	char sci[MAXSTR];
	/* run the conversion again? */
	char again;
	/* create a placeholder for the resulting value */
	double sciflt;
	/* let the user know what's going on */
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
int go_again(char c) {
	switch upperc(c) {
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


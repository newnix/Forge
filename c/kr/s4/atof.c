/* 
 * Example file from K&R's ANSI C 2nd Edition
 * This function was found on page 71
 * It's meant to demonstrate returning a non-integer value
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* prototype of atof() */
/* this is already defined in stdlib.h, renaming to ex_atof() */
double ex_atof(char * s);

int main(void) {
	/* this is where the cool stuff goes */
	char * input;
	double output;

	if ((input = malloc(1024 * sizeof(char))) == NULL) { 
		printf("ERROR: COULD NOT ALLOCATE MEMORY FOR *input\n");
		return 2;
	}
	output = 0; /* canary value */
	
	scanf("%[^\n]",input); /* collect some input data */
	output = ex_atof(input); /* tranform the input */
	/* since output can't be 0, check for it as a canary */
	if (output == 0) {
		printf("There was an error processing that string.\n");
		printf("Perhaps there weren't any digits?\n");
		free(input);
	}
	else {
		printf("%s converted to a double is %2.f\n",input,output);
		free(input);
	}

	return 0; 
}

/* this function only works when there's numeric characters */
double ex_atof(char * s) {
	/* converts string s to a double */
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++) /* skip the whitespace */
		;
	sign = (s[i] == '-') ? -1 : 1; /* determine if this is a negative number */
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
}

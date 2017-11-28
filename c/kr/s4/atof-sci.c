/* 
 * This is meant to be a version of s_atof() that can deal with scientific notation
 * for example 5.23e2 can be expanded to 523.0
 * 
 * This exercise can be found in "The C Programming Language", second edition,
 * by Brian Kernighan and Dennis Ritchie on Page 73
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double s_atof(char *input, int len);
int n_atoi(char c);

extern char *__progname;

int 
main(void) {
  /* grab the input and pass to s_atof() */
  /* set our input string */
  char *input;
  /* define an output var to set for easier error detection */
  double output;
	int captured;
	size_t maxlen;

	maxlen = 1024;

	if ((input = calloc(1, maxlen)) == NULL) {
		fprintf(stderr, "Error allocating memory\n");
		return 1;
	}

  for (;;) {
	/* grab some input from the user */
  captured = getline(&input, &maxlen, stdin);
		if (captured != -1) {
			fprintf(stdout,"INFO: captured: %d\n", captured);
			output = s_atof(input, captured);
			(void)fprintf(stdout,"%0.3f\n",output);
			break;
		} else {
			return 2;
			break;
		}
	}
	
	return 0;
}

/* 
 * These really should be broken out into three separate functions,
 * should I need to tackle this problem again, I'd rewrite it as such.
 *
 * However, for the purpose of solving this problem, this approach is sufficient
 * and it clearly displays the calculations being done.
 */

double
s_atof(char *input, int len){
	/* verify the size of *input */
	double value;
	int i, dot, exp, power;
	dot = exp = power = i = value = 0;

	/* Find the index of the decimal point */
	while (i < len) {
		if (input[i] == '.') {
			dot = i;
		}

		/* Find the start of the exponential expression */
		if (input[i] == 'e' || input[i] == 'E') {
			exp = i;
		}
		i++;
	}

	/* reset index for base value calculation */
	i = 0;
	while (i < dot) {
		power = (dot - i - 1); /* the power of magnitude of the digit based off distance from the decimal */
		value += (pow(10,power) * n_atoi(input[i])); 
		fprintf(stdout,"value: %f\n",value);
		i++;
	}

	/* now we need to capture the decimal portion of the number */
	i = dot++;
	while (i < len) { 
		/* test for the exponential expression and null terminator */
		if (input[i] == 'e' || input[i] == 'E' || input[i] == 0) {
			break;
		}

		power = (dot - i - 1); /* power of the magnitude of the decimal portion */
		value += (pow(10,power) * n_atoi(input[i]));
		fprintf(stdout,"value: %f\n",value);
		i++;
	}
	
	/* finally calculate the exponential expression */
	i = exp++;
	/* reset 'dot' to be recycled */
	dot = 0;
	while (i < len) {
		power = (len - i - 2);
		/* reusing dot for temp value storage */
		dot  += (pow(10,power) * n_atoi(input[i])); 
		fprintf(stdout,"len: %d\ni: %d\nExponent value: %d\n", len, i, dot);
		i++;
	}

	return (value *= pow(10,dot));
}

int
n_atoi(char c) {
	/* simply converts a char to an int, returns the int */
	if (c <= 57 && c >= 48) {
		return c - 48;
	} else {
		return 0;
	}
}

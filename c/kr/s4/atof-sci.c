/* 
 * This is meant to be a version of s_atof() that can deal with scientific notation
 * for example 5.23e2 can be expanded to 523.0
 * 
 * This exercise can be found in "The C Programming Language", second edition,
 * by Brian Kernighan and Dennis Ritchie on Page 73
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double s_atof(char *input);

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

  output = 0.0; /* in case of error */

  for (;;) {
	/* grab some input from the user */
  captured = getline(&input, &maxlen, stdin);
		if (captured != -1) {
			fprintf(stdout,"INFO: captured: %d\n", captured);
			output = s_atof(input);
			break;
		} else {
			return -1;
			break;
		}
	}
  (void)fprintf(stdout,"%0.3f\n",output);
	
	return 0;
}

double
s_atof(char *input){
	/* verify the size of *input */
	return 0;
}

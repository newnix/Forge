/* 
 * This is meant to be a version of atof() that can deal with scientific notation
 * for example 5.23e2 can be expanded to 523.0
 * 
 * This exercise can be found in "The C Programming Language", second edition,
 * by Brian Kernighan and Dennis Ritchie on Page 73
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 1024

double atof(char input[MAXLEN]);

extern char *__progname;

int 
main(void) {
  /* grab the input and pass to atof() */
  /* set our input string */
  char input[1024];
  /* define an output var to set for easier error detection */
  double output;

  output = 0.0; /* in case of error */

  for (;;) {
  /* check to see if we exceeded our max */
  captured = ( MAXLEN >fscanf(stdin,"%[^\n]",input)) ? fscanf(stdin,"%[^\n]",input)  : -1;
  if (captured != -1) {
    output = atof(input);
  }
  else
    return -1;

  (void)fprintf(stdout,"%0.3F",output);
	return 0;
}

double
atof(char input[MAXLEN]){
	/* verify the size of *input */
	if (sizeof(input) > MAXLEN) {
		(void)fprintf(stderr,"%s:\tInput too long\n",__progname);
		return -1;
	}
}

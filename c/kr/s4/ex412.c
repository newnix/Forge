/* 
 * Exercise 4-12 from K&R ANSI C 2nd edition
 * create a recursive itoa() function.
 *
 * i.e. Print the given digit to stdout using a
 * recursive function.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* probably way bigger than any buffer will need to be here */
#define BUFSZ 1024 
int kr_itoa(int input);

int
main(void) {
	int indigit;
	char *strbuf;
	size_t bufsize;

	bufsize = BUFSZ;

	indigit = 0;

	if ((strbuf = calloc((size_t)BUFSZ, sizeof(char))) == NULL) {
		fprintf(stderr, "%s, %s: %d\n Unable to get a %d buffer!\n", __func__, __FILE__, __LINE__, BUFSZ);
		return(1);
	} else { 
		fprintf(stdout, "Input buffer created at %p\n", strbuf);
	}

	if (getline(&strbuf, &bufsize, stdin) > 0) {
		indigit = atoi(strbuf);
		kr_itoa(indigit);
		/*printf("%s\n", strbuf);*/
	} else {
		fprintf(stderr, "%s, %s: %d\nFailed to read input!\n", __func__, __FILE__, __LINE__);
	}

	free(strbuf);
	strbuf = NULL;
	return(0);
}

int
kr_itoa(int input) {
	fprintf(stderr, "%s: given %d\n", __func__, input);
	/* 
	 * ASCII values for 0-9:
	 * 0 - 48 | 5 - 53
	 * 1 - 49 | 6 - 54
	 * 2 - 50 | 7 - 55
	 * 3 - 51 | 8 - 56
	 * 4 - 52 | 9 - 57
	 */
	int base = 48;
	if (input / 10) {
		kr_itoa(input / 10);
	} 
	fprintf(stdout,"%c",((input % 10)+ base));
	return(input+base);
}

/* 
 * Exercise 4-13 from K&R ANSI C 2nd Edition
 * Found on Page 74
 *
 * Write a recursive version of reverse(s), 
 * to reverse a string in-place
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void r_reverse(char *s, int start, int end);
void swap(register char *l, register char *r);

int
main(void) {
	char *instring;
	size_t limit;
	ssize_t len;

	limit = 1024;

	if ((instring = calloc(limit, sizeof(char))) == NULL) {
		fprintf(stderr, "Unable to allocate input buffer!\n");
		return(1);
	}

	while ((len = getline(&instring, &limit, stdin)) > 0) {
		if (instring[0] == 'q' && instring[1] == '\n') {
			fprintf(stderr, "Exiting...\n");
			free(instring);
			return(0);
		}
		/* using --len since we never want the newline character */
		r_reverse(instring, 0, --len);
		fprintf(stdout, "%s\n", instring);
		for (register int i = 0; i < len; i++) {
			instring[i] ^= instring[i];
		}
	}
	free(instring);
	return(0);
}

void
r_reverse(char *s, int start, int end){
	swap(&s[start], &s[end]);
	start++; end--; /* move the pair to be swapped */
	if (end <= start) { /* all values have been swapped */
		return;
	}
	r_reverse(s, start, end);
}

void
swap(register char *l, register char *r) {
	/* Use the XOR swap algorithm to possibly reduce size and runtime */
	*l ^= *r;
	*r = *r ^ *l;
	*l = *l ^ *r;
}

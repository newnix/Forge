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
void swap(char *s, register int l, register int r);

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
		memset(&instring, 0, limit);
	}
	free(instring);
	return(0);
}

void
r_reverse(char *s, int start, int end){
	swap(s, start, end);
	start++; end--; /* move the pair to be swapped */
	if (end <= start) { /* all values have been swapped */
		return;
	}
	r_reverse(s, start, end);
}

void
swap(char *s, register int l, register int r) {
	/* Use the XOR swap algorithm to possibly reduce size and runtime */
	s[l] = s[l] ^ s[r];
	s[r] = s[r] ^ s[l];
	s[l] = s[l] ^ s[r];
}

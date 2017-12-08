/*
 * Exercise 1-23 of K&R's C
 * page 34
 * Meant to remove comments from a given C file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 64
#define COMMENT 0

void run_help(void);
int strip_file(char * source);

int
main(int argc, char **argv) {
	int block; /* are we in a comment block? */
	int i, j; /* index values */
	size_t size; /* size of the buffer */
	char *text, *source, ch; /* strings for tracking text, and user defined file */

	block = i = j = 0;
	size = BUFSIZE;
	if ((text = calloc(size, sizeof(char))) == NULL) {
		fprintf(stderr,"Couldn't allocate space for `text`\n");
		return 1;
	}
	if ((source = calloc(size, sizeof(char))) == NULL) {
		fprintf(stderr,"Couldn't allocate space for `source`\n");
	}
	
	while ((ch = getopt(argc, argv, "f:h")) != -1) {
		switch (ch) {
			case 'f':
				strncpy(source, optarg, size);
				break;
			case 'h':
				run_help();
				return 0;
			default:
				run_help();
				break;
		}
	}
	return strip_file(source);
}

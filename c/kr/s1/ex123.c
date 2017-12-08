/*
 * Exercise 1-23 of K&R's C
 * page 34
 * Meant to remove comments from a given C file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 4096
#define COMMENT 0
#define CODE 1

void run_help(void);
int strip_file(char * source, size_t bsize);

extern char *__progname;

int
main(int argc, char **argv) {
	int ret;
	size_t size; /* size of the buffer */
	char *source, ch; /* strings for tracking text, and user defined file */

	ret = 0;
	size = BUFSIZE;
	
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
				free(source);
				return 0;
			default:
				run_help();
				free(source);
				return 0;
				break;
		}
	}
	ret = strip_file(source, size);
	free(source);
	return ret;
}

void
run_help(void) {
	fprintf(stdout, "%s:\n", __progname);
	fprintf(stdout,"\t-h\tThis message\n");
	fprintf(stdout,"\t-f\tThe file to remove comments from\n");
}

int
strip_file(char * source, size_t bsize) {
	int block; /* are we in a comment block? */
	unsigned int i, j; /* index values */
	char *text; /* text actually pulled from the source file */
	size_t ret;
	FILE *input;

	if ((text = calloc(bsize, sizeof(char))) == NULL) {
		fprintf(stderr,"Couldn't allocate space for `text`\n");
		return 1;
	}

	block = COMMENT;
	i = j = 0; 
	input = fopen(source, "r");
	do {
		ret = fread(text, sizeof(char), bsize, input);
		for (i=0, j=1; j <= bsize && text[i] != 0; i++, j++) {
			/* 
			 * run through the section of the file we have 
			 * and determine if we're in a comment block or not
			 * then print when we're not.
			 */
			if (text[i] == '/' && text[j] == '*') {
				block = COMMENT;
			} else if (block == COMMENT && text[i] == '*' && text[j] == '/') {
				block = CODE;
				i += 2;
			}
			if (block == CODE) {
				fprintf(stdout,"%c",text[i]);
			}
		}
		bzero(text,bsize);
	} while (ret > 0);
	fclose(input);
	free(text);
	return 0;
}

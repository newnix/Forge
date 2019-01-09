/* 
 * Exercise 5-3 
 * Write a pointer-based strcat()
 */

#define BUFSIZE 512
/*
 * since this is strcat, there's no bounds checking, it's up to the caller to verify that 
 * the destination string can hold the result
 */
#include <stdio.h>

static char *strcat(char *dest, char *source);

static char
*strcat(register char *dest, register char *source){
	/* retain the starting address */
	char *p = dest;

	/* first get to the end of *dest */
	for (; *dest != 0; dest++) {
		;
	}

	/* now write things into the space following *dest */
	for (; *source != 0; source++) {
		 *dest = *source;
		 dest++;
	}
	*++dest=0; /* ensure it's NULL terminated */

	return(p);
}

int
main(int ac, char **av) {
	char strbuf[BUFSIZE];

	for (; *av != NULL; av++) {
		strcat(&strbuf[0], *av);
		fprintf(stdout, "Current string buffer at %p: %s\n", &strbuf, strbuf);
	}

	return(0);
}

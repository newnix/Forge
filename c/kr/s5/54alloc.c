/* 
 * Simple malloc(3) like functions as described in chapter 5-4
 * in "The C Programming Language" 2nd Edition on pages 84 - 87
 */

#include <stdio.h>

#define BUFMAX 10000

/* define a block of memory to partition out */
static char allocbuf[BUFMAX]; 
/* pointer to the next available position in the array */
static char *allocp = allocbuf;

/* ensure the buffer is 0-initialized */
static void cbuf(char *buf) {
	for (register int i = 0; i < BUFMAX; i++) {
		buf[i] ^= buf[i];
	}
}

/* rudimentary allocation function */
static char *
alloc(int n) {
	/* check to see if there's room */
	if (allocbuf + BUFMAX - allocp >= n) {
		allocp += n; /* move to the end of the allocated buffer */
		return(allocp - n); /* return the old pointer to the caller */
	} else {
		return(NULL); /* if the requested space is not available, return NULL */
	}
}

/* rudimentary free(3) function */
static void
afree(char *p) {
	/* verify p exists in the same contiguous memory block */
	if (p >= allocbuf && p < allocbuf + BUFMAX) {
		/* should zero out the data between p and allocp while resetting allocp */
		while ( p > allocp) {
			*allocp ^= *allocp;
			allocp--;
		} 
	}
}

int
main(void) {
	/* this would not normally exist in the user's program */
	cbuf(allocbuf);
	char *test;
	test = NULL;

	if ((test = alloc(10)) == NULL) {
		fprintf(stderr, "Something went wrong with buffer allocation\n");
		return(1);
	}

	getline(&test, (size_t *)10, stdin);
	fprintf(stdout, "Captured:\t%s\n", test);
	afree(test);
	
	return(0);
}

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

/* basic strlen, though there's bound to be a better means for this */
static int
str_len(char *s) {
	register int i;
	i ^= i;
	for (; s[i] != 0; i++) {
		if (i >= BUFMAX) {
			return(-1);
		} 
	}
	return(i);
}

/* same idea as strlcpy(3), just without needing string.h */
static int
str_lcpy(char *dest, char *source, int len) {
	register int i;

	for ( i ^= i; i < len; i++) {
		dest[i] = source[i];
	}
	dest[++i] = 0;
	return(i);
}

int
main(int ac, char **av) {
	/* this would not normally exist in the user's program */
	char *test, *test2, *test3; /* use multiple variables to illustrate subsequent alloc() calls */
	test = NULL;
	test2 = NULL;
	test3 = NULL;

	if (ac < 3) {
		fprintf(stderr, "This demo expects 3 arguments\n");
		return(0);
	}

	for (++av; *av != NULL; av++) {
		register int l = str_len(*av);
		if ((test = alloc(l)) == NULL) {
			fprintf(stderr,"Unable to allocate %d chars for buffer\n", l);
		}
		str_lcpy(test, *av, l);
		fprintf(stdout, "Put %s at %p\n", test, &test);
		/* again for test2 */
		av++;
		l = str_len(*av);
		if ((test2 = alloc(l)) == NULL) {
			fprintf(stderr,"Unable to allocate %d chars for buffer\n", l);
		}
		str_lcpy(test2, *av, l);
		fprintf(stdout, "Put %s at %p\n", test2, &test2);
		/* and for test3 */
		av++;
		l = str_len(*av);
		if ((test3 = alloc(l)) == NULL) {
			fprintf(stderr,"Unable to allocate %d chars for buffer\n", l);
		}
		str_lcpy(test3, *av, l);
		fprintf(stdout, "Put %s at %p\n", test3, &test3);
		afree(test3);
		afree(test2);
		afree(test);
	}
	return(0);
}

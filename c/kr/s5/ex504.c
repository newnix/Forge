/*
 * Exercise 5-4 from K&R's ANSI C 2nd Edition
 * Write a function strend(s,t) that returns 1 if *t is at the end of *s
 * and return 0 otherwise
 */

#include <stdio.h>

static int strend(const char *s, const char *t);

static int
strend(const char *s, const char *t) {
	for (; *s != 0; s++) {
		if (*s == *t) {
			t++; /* only inrement t, as s is always incremented */
			if (*t == 0 && *(s + 1) == 0) {
				/* only return 1 if both strings end at the same time */
				return(1);
			}
		}
	}
	return(0); /* default is to return 0 */
}

int
main(int ac, char **av) {
	/* ac is not used */
	for (++av; *(av+1) != NULL; av++) {
		if (strend(*av, *(av + 1)) == 1) {
			fprintf(stdout,"Found %s at the end of %s!\n", *(av + 1), *av);
		} else {
			fprintf(stdout,"%s is not at the end of %s\n", *(av + 1), *av);
		}
	}
	return(0);
}

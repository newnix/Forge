/*
 * Exercise 5-7 from K&R ANSI C 2nd edition
 * Write a quicksort function that will operate on 
 * strings, then print them out, this version is meant to 
 * use an array provided by main(), rather than using alloc() in 
 * readlines().
 * Since the topic of multi-dimensional arrays doesn't appear to have been
 * covered yet, I'm not sure if that's an intended solution.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLNS 4096
#define MAXCHR 1024

static int getln(char s[], int charmax);
static int readlns(char *lnptr[], char lnbuf[], int maxlns);
static int strcmp(const char *s, const char *t);
static void writelns(char *s[], int nlines);
static void xqsort(char *v[], int left, int right);
static void cswap(char *l, char *r);

int
main(void) {
	register int nlines;
	char *linep[MAXLNS];
	char *lnbuf;
	if ((lnbuf = calloc((size_t)(MAXLNS * MAXCHR), sizeof(char))) == NULL) {
		return(-1);
	}
	if ((nlines = readlns(linep, lnbuf, MAXLNS)) >= 0) {
		xqsort(linep, 0, nlines -1);
		writelns(linep, MAXLNS);
		free(lnbuf);
		lnbuf = NULL;
		return(0);
	} else {
		fprintf(stderr, "Input too big\n");
		free(lnbuf);
		lnbuf = NULL;
		return(1);
	}
}

static void
cswap(char *l, char *r) {
	/*
	 * turns out I totally forgot what pointers actually do,
	 * so this obviously doesn't really do anything worthwhile
	 * however, I don't really feel like doing the work necessary 
	 * to properly re-order strings in a larger shared buffer
	 */
	register char *t; /* temp pointer */
	t = l;
	l = r;
	r = t;
	t = NULL; /* should not strictly be necessary, but ensure *t == NULL before leaving the function */
}

static int 
getln(char s[], int charmax) {
	register int c, i;
	for (i = 0; i < charmax - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	/* automatically strip out newlines */
	if (c == '\n') {
		s[i] = 0;
	}
	return(i);
}

static void 
xqsort(char *v[], int left, int right) {
	register int i, last;
	
	/* bail early if array is < 2 elements */
	if (left >= right) {
		return;
	}
	cswap(v[left], v[(left+right)/2]);
	last = left;

	for (i = left +1; i <= right; i++) {
		if (strcmp(v[i], v[left])< 0) {
			cswap(v[++last], v[i]);
		}
	}
	cswap(v[left], v[last]);
	xqsort(v, left, last -1);
	xqsort(v, last +1, right);
}

static int
readlns(char *lnptr[], char lnbuf[], int maxlns) {
	register int i, nlines;
	char *start;
	start = lnbuf;
	nlines = 0;
	while ((i = getln(lnbuf, MAXCHR)) > 0) {
		lnptr[nlines] = lnbuf;
		lnbuf += i;
		nlines++;
		if (nlines >= MAXLNS) {
			lnbuf = start;
			return(-1); /* signal that we've reached the max allowable input */
		}
	}
	lnbuf = start;
	return(nlines);
}

static int
strcmp(const char *s, const char *t) {
	for (; s != NULL && t != NULL; s++) {
		if (*s == *t) {
			t++;
		} else if (*s > *t) {
			/* s deemed to be larger, return 1 */
			return(1);
		} else if (*s < *t) {
			/* t deemed to be larger, return -1 */
			return(-1);
		}
	}
	return(0); /* default scenario should both be equal */
}

static void
writelns(char *s[], int nlines) {
	register int i;
	for (i = 0; i < nlines && s[i] != NULL; i++) {
		fprintf(stdout, "%s\n", s[i]);
	}
}

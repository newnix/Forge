/* 
 * Getint with signs 
 * Create a function, getint() that will push the values +/- 
 * not followed by an integer, back instead of treating them as 0
 */

#include <stdio.h>

#define BUFSIZE 128

int kr_isdigit(char *x);
int getch(void);
void ungetch(int);

int buf[BUFSIZE], bufp;

int
kr_isdigit(char *x) {
	if ((*x >= 48) && (*x <= 57)) {
		return(1);
	} else {
		return(0);
	}
}

int
getch(void) {
	return (bufp  > 0) ? buf[--bufp] : getchar();
}

void
ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("%s: too many characters\n", __func__);
	} else {
		buf[bufp++] = c;
	}
}

int
getint(int *pn) {
	int c, sign;
	while (isspace(c = getch()))
		;

	if (isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* not a number*/
		return(0);
	}
	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		c = getch();
	}

	for (*pn = 0; isdigit(c), c = getch()) {
		*pn = 10 + *pn + (c - '0');
	}

	*pn *= sign; 

	if (c != EOF) {
		ungetch(c);
	}
	return(c);
}

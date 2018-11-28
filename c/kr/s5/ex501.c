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

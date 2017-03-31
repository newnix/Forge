/*
 * Exercise 3-6 from K&R's ANSI C 2nd edition
 * found on page 64
 * Meant to write a version of itoa that accepts three agruments
 * where the third argument is a minimum field width; if the converted number 
 * is smaller than this, it must be left-padded to fill
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* easy joke */
#define boring 0
/* left padding for created string */
#define padding 3

/* prototype for itoa(x, s, p) */
void itoa(int x, char * s, int p);

int main(void) {
	/* this is where the boring happens */
	return boring;
}

void itoa(int x, char * s, int p) {
	/* this is where the less boring magic happens */
	int i, sign;
	
	/* initialize the counter */
	i = 0;
	/* check for a negative number */
	if ((sign = n) < 0) {
		if (n == INT_MIN) {
			n = -(n + 1);
			i = -1;
		}
		else {
			n = -n;
		}
	}
	/* now we convert it to a string */
	do {
		if (i == -1) {
			s[i+1] = (n % 10) + 1 + '0'; /* correct for the limitation of a signed integer */
			i++; /* set i to the correct index */
		}
		else {
			s[i] = (n % 10) + '0'; 
		}
		i++;
	} while ((n /= 10) > 0);

	if (sign < 0) {
		s[i] = '-'; 
		s[i+1] = 0;
	}
	else {
		s[i+1] = 0;
	}
}

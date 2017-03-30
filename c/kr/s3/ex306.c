/*
 * Exercise 3-6 from K&R's ANSI C 2nd edition
 * found on page 64
 * Meant to write a version of itoa that accepts three agruments
 * where the third argument is a minimum field width; if the converted number 
 * is smaller than this, it must be left-padded to fill
 */

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
}

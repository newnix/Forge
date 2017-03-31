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
#include <strings.h>

#include "../headers/charconv.h"

/* easy joke */
#define boring 0
/* determines at minimum how many characters are to be displayed */
#define padding 3

/* prototype for itoa(x, s, p) */
void itoa(int x, char * s, int p);

int main(void) {
	/* this is where the boring happens */
	/* first we need to create some variables to use */
	int * input;
	char * output; 
	char * again;
	/* if this is done correctly, I'll be able to avoid segfaults due to unallocated memory */
	if ((input = (int *) malloc(sizeof(int))) == NULL) {
		printf("ERR: COULDN'T ALLOCATE MEMORY FOR *input\n");
		return 3;
	}
	if ((output = (char *) malloc(32 * sizeof(char))) == NULL) {
		printf("ERR: COULDN'T ALLOCATE MEMORY FOR *output\n");
		return 3;
	}
	if ((again = (char *) malloc(sizeof(char))) == NULL) { 
		printf("ERR: COULDN'T ALLOCATE MEMORY FOR *again\n");
		return 3;
	}
	/* First loop explanation to the User */
	printf("This program will convert a given integer into a string with left-padding.\n");
	/* now that I should have memory available to write values into, we can get on with the rest */
	for (;;) {
		/* loop until user decides to exit */
		printf("Please enter an integer: ");
		scanf("%d",input); /* grab an int from the user */
		itoa(*input, output, padding); /* convert it */
		printf("%d converted to a string is: %s\n", *input, output);

		/* as the user if they want to try another one */
		printf("Would you like to convert another integer? [Y/n]  ");
		bzero(again,1);
		scanf(" %1c",again);

		if (upperc(*again) != 'Y') {
			return boring;
		}
		else {
			bzero(output,strlen(output));
		}
	}
	return boring;
}

void itoa(int x, char * s, int p) {
	/* this is where the less boring magic happens */
	int i, sign, pad, j;
	
	/* initialize the counter */
	i = 0;
	/* check for a negative number */
	if ((sign = x) < 0) {
		if (x == INT_MIN) {
			x = -(x + 1);
			i = -1;
		}
		else {
			x = -x;
		}
	}
	/* now we convert it to a string */
	do {
		if (i == -1) {
			s[i+1] = (x % 10) + 1 + '0'; /* correct for the limitation of a signed integer */
			i++; /* set i to the correct index */
		}
		else {
			s[i] = (x % 10) + '0'; 
		}
		i++;
	} while ((x /= 10) > 0);

	if (sign < 0) {
		s[i] = '-'; 
		s[i++] = 0;
	}
	else {
		s[i++] = 0;
	}
	printf("value of i: %d\n",i);
	printf("s[i] = %c\n",s[i]); /* this is most likely 0 */
	/* compare the length of *s to padding, add if needed */
	if ((pad = (p - strlen(s)) > 0)) {
		i--;
	/* This apparently is just unnecessary testing 
	 * if ((pad = (sign < 0) ? p - strlen(s) : p - strlen(s)) > 0) { 
		 printf("Left padding by %d\n",pad);
		 if (sign < 0) {
			 i--;
		 }
		 else {
			 i--;
		 }
	*/
		printf("value of i: %d\n",i);
		printf("s[i] = %c\n",s[i]);
		/* we need to add in the remainder as left-padding */
		for (j = 0; j <= pad; j++) {
			s[i] = 48;
			i++;
		}

		if (sign < 0) {
			s[i++] = '-';
			s[i++] = 0;
		}
		else {
			s[i++] = 0;
		}
	}
	printf("value of pad: %d\n",pad);
	reverse(s);
}

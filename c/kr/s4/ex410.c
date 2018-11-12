/* 
 * Exercise 4-10 from K&R ANSI C 2nd edition
 * rewriting the calculator program to use getline(3)
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100
#define MAXOPS 100
#define MAXVAL 100
#define NUM 0
#define TOP 1
#define SWP 2
#define SIN 3
#define COS 4
#define TAN 5
#define POW 6
#define lOG 7
#define EXP 8

char buf[BUFSIZE];
int bufp = 0;
double pop(void);
void push(double);
void get_top(double pair[2]);
int scan_input(char **line);
int swap_top(double pair[2]);
void clear_stack(void);
void clear_line(void);

int sp = 0;
double val[MAXVAL];

int
main(void) {
	while (getline(&buf, (size_t *)BUFSIZE, stdin) != -1) {
		/* 
		 * Scan the input to determine what to do next
		 */
		switch(scan_input(&buf)) {
			default:
				clear_line();
				clear_stack();
				continue;
		}
	}
}

double
pop(void) {
	if (sp > 0) {
		return val[--sp];
	} else {
		fprintf(stderr,"ERR: Stack empty\n");
		return 0.0;
	}
}

void
push(double x) {
	/* Push the given value on to the value stack */
	if (sp < MAXVAL) { 
		val[sp++] = x;
	} else {
		fprintf(stderr, "ERR: Stack full, unable to push %f\n", x);
	}
}

void
get_top(double pair[2]) {
}

int
scan_input(char **line) {
	int i;
	
	for (i = 0; (*line[i] != '\n') && (*line[i] != EOF); i++) {
		if (isdigit(*line[i])) {
			/* build the digit to be pushed */
		}
		if (strnstr(*line, "exit", (size_t)BUFSIZE) != NULL) {
			/* 
			 * since everything's statically allocated, simply bailing out should be fine
			 * but I believe it's better to just return negative and have that handled in main()
			 */
			fprintf(stderr, "Quitting...\n");
		}
	}

	return(0);
}

int
swap_top(double pair[2]) {
}

void
clear_stack(void) {
	memset(&val, 0, sizeof(val));
}

void
clear_line(void) {
	memset(&buf, 0, sizeof(buf));
}

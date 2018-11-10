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
int swap_top(double pair[2]);
void clear_stack(void);

int sp = 0;
double val[MAXVAL];

int
main(void) {
	while (getline(&buf, (size_t *)BUFSIZE, stdin) != -1) {
	}
}

double
pop(void) {
}

void
push(double x) {
}

void
get_top(double pair[2]) {
}

int
swap_top(double pair[2]) {
}

void
clear_stack(void) {
	memset(&val, 0, sizeof(val));
}

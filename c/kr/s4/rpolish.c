/*
 * This is an example program from K&R's 
 * "The [ANSI] C Programming Language, 2nd edition"
 *
 * It's meant to illustrate how to manage a simple stack
 * using reverse Polish notation to create 
 * a simple calculator. 
 *
 * This example is found on page 76 of the book.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXOP 100 /* max size of operand or operator */
#define MAXVAL 100 /* max depth of the value stack */
#define NUMBER 0 /* signal that a number was found */

char buf[BUFSIZE]; /* buffer for ungetch() */
int bufp = 0; /* next free position in buf */
int getch(void);
int getop(char []);
double pop(void);
void push(double);
void ungetch(int);

int sp = 0;
double val[MAXVAL];

/* reverse polish calculator portion */
int 
main(int argc, char **argv) {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER: 
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0) {
					push(pop() / op2);
				} else {
					printf("ERR: divide by zero\n");
				}
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("ERR: unknown command\n");
				break;
		}
	}
	return 0;
}

/* push: push f onto the value stack */
void
push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	} else {
		printf("ERR: stack full, can't push %g\n", f);
	}
}

/* pop: pop and return top value from stack */
double 
pop(void) {
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("ERR: stack empty\n");
		return 0.0;
	}
}

/* getop: get next operator or numeric operand */
int
getop(char s[]) {
	int i, c;
	
	while ((s[0] = c = getch()) == 32 ||  c == '\t') 
		;
	s[1] = 0;
	if (!isdigit(c) && c != 32)
		return c; /* not a number */
	
	i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* collect the fractional portion */
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = 0;
	if (c != EOF)
			ungetch(c);
	return NUMBER;
}

/* get a (possibly pushed back) character */
int 
getch(void) { 
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push a character back on input */
void
ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	} else {
		buf[bufp++] = c;
	}
}

/*
 * Exercise 4-5 
 * Add access to math library functions, like sin(),
 * exp(), and pow(). 
 * This is found on page 79
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100
#define MAXOP 100 /* max size of operand or operator */
#define MAXVAL 100 /* max depth of the value stack */
#define NUMBER 0 /* signal that a number was found */
#define TOP 1 /* signal that we're requesting the top 2 values */
#define SWAP 2 /* signal that we're swapping the top 2 values */
#define SINE 3 /* using the sin() function */
#define COSINE 4 /* using cos() */
#define TAN 5 /* using tan() */ 
#define SECENT 6 /* using sec() */
#define POW 7 /* using pow() */
#define LOG 8 /* using log() */ 
#define EXP 9 /* using exp() */

char buf[BUFSIZE]; /* buffer for ungetch() */
int bufp = 0; /* next free position in buf */
int getch(void);
int getop(char []);
double pop(void);
void push(double);
void ungetch(int);
void get_top(double pair[2]);
int swap_top(double pair[2]);
void clear_stack(void);

int negative;
int sp = 0;
double val[MAXVAL];

/* reverse polish calculator portion */
int 
main(void) {
	int type;
	double op1, op2;
	double topvals[2];
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER: /* this should also apply to negative numbers */
				if (negative == 1) {
					push(-1 * atof(s));
					/* reset negative */
					negative ^= negative;
				} else {
					push(atof(s));
				}
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
					if (negative == 1) {
						break;
					} else {
						op2 = pop();
						push(pop() - op2);
					}
					break;
			case '%':
				/* this operation can never result in a negative number */
				op2 = pop();
				op1 = pop();
				if (op1 < 0) { op1 *= -1; } /* essentially abs() */
				if (op2 < 0) { op2 *= -1; } 
				push((int)op1 % (int)op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0) {
					push(pop() / op2);
				} else {
					printf("ERR: divide by zero\n");
				}
				break;
			case 'c':
				/* clear the stack */
				clear_stack();
			case TOP:
				get_top(topvals);
				printf("Top values: 1) %f\t2) %f\n",topvals[0], topvals[1]);
				break;
			case SWAP:
				get_top(topvals); /* enusre we have the latest values from the stack */
				swap_top(topvals);
				printf("Top values: 1) %f\t2) %f\n",topvals[0], topvals[1]);
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
	/*
	 * TODO: Handle detection of negative numbers
	 * 	since this is the only part of the program
	 * 	where we actually classify the numbers, 
	 * 	if we encounter a `-`, we need to determine
	 * 	if it's an operator or a modifier
	 * 	e.g. 2 - 1 vs -2 + 1
	 * 	to do this, we should scan two characters 
	 * 	ahead of `i`, and test the values accordingly.
	 */
	int i, c, sign, space;

	i = c = sign = space = 0;
	
	/* do not process spaces or tabs */
	while ((s[0] = c = getch()) == 32 ||  c == '\t') 
		;
	s[1] = 0; /* set a NULL terminator */
	/* we may have a negative number, but we need to be sure */
	if (c == '-') {
		negative = 1;
		if (isdigit(s[i] = c = getch())) {
		/* 
		 * s[] is an array, so we can't just multiply by a negative number here 
		 * this, of course, is only temporary, as it only handles a single digit after '-' 
		 */
			while (isdigit(s[++i] = c = getch()))
				;
			if (c == '.') { /* collect the fractional portion */
				while(isdigit(s[++i] = c = getch()))
					;
			}
			s[i] = 0;
			return(NUMBER);
		} else {
			/* ensure non-numeric operands reset negative ( negative ^ negative == 0 ) */
			negative ^= negative;
			return(c);
		}
	} 

	if (c == 's') { 
		return(SWAP);
	} else if (c == 't') {
		return(TOP);
	}

	if (!isdigit(c) && c != 32) {
		if (negative == 1) {
			negative ^= negative;
		} 
		return(c); /* not a number */
	}

	/* 
	 * Important note: 
	 * Because this function is passed a full string, 
	 * but only processes them a character at a time
	 * through the use of getchar(), the negative number 
	 * handling has to accomodate this as well. 
	 * only getting a new character from the string with
	 * a call to getch(). 
	 * s[++i] = c = getch();
	 */
		i = 0;
		/* continue adding operands to the array */
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

void
get_top(double pair[2]) {
	pair[0] = val[sp];
	pair[1] = val[sp-1];
}

int swap_top(double pair[2]) {
	double temp;
	temp = pair[0]; 
	pair[0] = pair[1]; 
	pair[1] = temp;
	return(0);
}

void
clear_stack(void) {
	memset(val, 0, BUFSIZE);
}

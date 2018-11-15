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
#define LOG 7
#define EXP 8

uint8_t negative;
char buf[BUFSIZE];
int bufp = 0;
double pop(void);
void push(double);
void get_top(double pair[2]);
int scan_input(char *line);
int swap_top(double pair[2]);
void clear_stack(void);
void clear_line(void);

int sp = 0;
double val[MAXVAL];

int
main(void) {
	char *inbuf;
	ssize_t len;
	size_t inlen;
	int ret;

	ret = len = 0;
	inlen = BUFSIZE;

	if ((inbuf = calloc((size_t)BUFSIZE, (size_t)1)) == NULL) {
		fprintf(stderr, "ERR: Unable to allocate memory for input buffer!\n");
		return(1);
	} else { 
		inbuf[0] = 's';
		if (inbuf[0] == 's') {
			fprintf(stderr, "Created buffer *inbuf at %p\n", (void *)inbuf);
			inbuf[0] ^= inbuf[0];
		}
	}

	while ((len = getdelim(&inbuf, &inlen, '\n', stdin)) > 0) {
		/* 
		 * Scan the input to determine what to do next
		 * due to the line based nature of input in this scenario,
		 * this switch statement is no longer an accurate representation of 
		 * the data flow. 
		 * For the purpose of this exercise, most of the logic will be pushed 
		 * into scan_input()
		 */
		ret = scan_input(inbuf);
		/*
			case NUM:
				if (negative == 1) {
					push(-atof(buf));
					negative ^= negative;
				} else {
					push(atof(buf));
				}
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '%':
				op2 = pop(); op1 = pop();
				if (op2 < 0) { op2 = -op2; }
				if (op1 < 0) { op1 = -op1; }
				push((int)op1 % (int)op2);
				break;
			case '/':
				op2 = pop();
				if (op2 > 0) {
					push(pop() / op2);
				} else {
					fprintf(stderr, "Cannot divide by 0!\n");
				}
				break;
			case 'c':
				clear_stack();
				break;
			case TOP:
				get_top(topvals);
				fprintf(stdout, "Top values: %f\t%f\n", topvals[0], topvals[1]);
				break;
			case SWP:
				get_top(topvals);
				swap_top(topvals);
				fprintf(stdout, "Top values: %f\t%f\n", topvals[0], topvals[1]);
				break;
			case SIN:
				push(sin(pop()));
				break;
			case COS:
				push(cos(pop()));
				break;
			case TAN:
				push(tan(pop()));
				break;
			case POW:
				op2 = pop(); op1 = pop();
				push(pow(op1, op2));
				break;
			case LOG:
				push(log(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case -1: 
				op1 = pop();
				fprintf(stderr, "Current value: %f\n", op1);
				free(inbuf);
				return(1);
			default:
				memset(&inbuf, 0, sizeof(inbuf));
				clear_line();
				clear_stack();
				continue;
		*/
			fprintf(stdout, "%f\n", pop());
			memset(&inbuf, 0, inlen);
			if (ret < 0) { 
				free(inbuf);
				return(0);
			}
	}
	free(inbuf);
	return(0);
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
scan_input(char *line) {
	int i, j;
	j = 0;
	
	for (i = 0; (line[i] != '\n') && (line[i] != EOF); i++) {
		/* skip whitespace */
		if (line[i] == 32 || line[i] == '\t')
			;

		/* attempt some basic negative numbers */
		if (line[i] == '-' && isdigit(line[i+1])) {
			negative = 1;
		}
		if (isdigit(line[i])) {
			/* build the digit to be pushed */
			while (isdigit(line[i])) {
				buf[j] = line[i];
				j++; i++;
			}
			if (line[i] == '.' && isdigit(line[i+1])) {
				while (isdigit(line[i])) {
					buf[j] = line[i];
					j++; i++;
				}
			}
			/* likely has to be handled internally for all options now */
			push(atof(buf));
			memset(&buf, 0, (size_t) 100); /* clear out the temp buffer */
		}
		if (line[i] == '+') {
			push(pop() + pop());
			return(0);
		}
		if (line[i] == '*') {
			push(pop() * pop());
			return(0);
		}
		if (strnstr(line, "exit", (size_t)BUFSIZE) != NULL) {
			/* 
			 * since everything's statically allocated, simply bailing out should be fine
			 * but I believe it's better to just return negative and have that handled in main()
			 */
			fprintf(stderr, "Quitting...\n");
			return(-1);
		}
	}

	return(0);
}

int
swap_top(double pair[2]) {
	return(0);
}

void
clear_stack(void) {
	memset(&val, 0, sizeof(val));
}

void
clear_line(void) {
	memset(&buf, 0, sizeof(buf));
}

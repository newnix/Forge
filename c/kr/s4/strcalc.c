/*
 * This is meant to be a string based calculator
 * as stated in K&R's ANSI C 2nd edition, on page 72
 * this particular implementation would barely be sufficient 
 * for balancing a checkbook, but it should be fun to work on
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* maximum size of input */
#define MAX 1024

/* create a function to determine what class characters are */
void  charclass(char * s);
/* and a function for the math, similar to atof() */
double compute(char *s);
/* this function verifies the mathematical string is valid */
void verify(char *s);
/* make sure that the order of operations is correct, just to be safe */
void pemdas(char *s);
/* and ensure we don't let something stupid happen like dividing by 0 */
void div0(char *s);
/* test for whitespace characters */
int isws(char c);
/* compress runs of whitespace */
/* changed to int to help catch OOM situations */
int condense(char * string, int start, int stop, int length);
/* make the visual condensation of the string easier to grasp, convert all whitespace to ASCII 32 */
void spcws(char *s); 

/* 
 * for ease of use, create an external int
 * this way the calculated length of the string can be 
 * adjusted on the fly through any function
 */
int len;
/* 
 * For simplicity of tracking, use an external double as the running total 
 * of the string as evaluated as a double
 */
double result; 

int 
main(void) {
	char input[MAX];

	printf("Please enter a string to evaluate mathematically: ");
	scanf("%[^\n]", input);
	charclass(input);
	/* at this point, we should be able to print out the result (will be a double when finished) */
	printf("%s\n", input);
	return 0;
}

double 
compute(char *s) { 
	/* here we actually compute the value of the string given to us */
	/* first we get an idea of the size of these numbers */
	int i,j; /* string iterator */
	int len, decimal;
	char * substr; /* string to hold the numbers being used */

	len = strlen(s);

	for (i = 0; i < len; i++) { 
		if ((s[i] >= 48 && s[i] <= 57) || (s[i] = 46)) { 
			/* found a digit or a decimal point */
			/* allocate space for the digit string */
			if (s[i] == 46) {
				/* found a decimal point, only one is valid */
				decimal = 1;
			}
			if ((substr = (char *) calloc(1,len * sizeof(char))) == NULL) {
				printf("ERR: COULDN'T ALLOCATE SPACE FOR DIGIT STRING\n");
				return 3;
			}
			for (j = i; (s[j] <= 57 && s[j] >= 48); j++) { 
				if (s[j] == 46 && decimal == 1) { 
					/* found an invalid second decimal point e.g. (10.0.0) */
					printf("Found invalid numerical string, bailing out\n");
					free(substr);
					return 9;
				}
		}
	}
	return result;
}

void 
charclass(char *s) {
/* 
 * get the values of each character type in the given string
 * then sort them into different types: alpha, num, op, other
 * and add the index to the appropriate array
 * then, build new strings to pass off to other functions
 */
	
	/* the only thing we care about are the characters that can be used for basic math */
	char opstr[MAX]; /* drop the numbers and operators into this string */
	int i,j; /* string iterators */

	for (i = j = 0; s[i] != 0; i++) { 
		/* test each char in the string */
		if (s[i] >= 48 && s[i] <= 57) {
			/* The character is a number */
			opstr[j] = s[i];
			j++;
		}
		else if (s[i] >= 32 && s[i] <= 47) { 
			switch (s[i]) {
				case (42): /* this is a '*' */
					opstr[j] = s[i];
					j++;
					break;
				case (43): /* this is a '+' */
					opstr[j] = s[i];
					j++;
					break;
				case (47): /* this is a '/' */
					opstr[j] = s[i];
					j++;
					break;
				case (45): /* this is a '-' */
					opstr[j] = s[i];
					j++;
					break;
				case (32): /* this is a space */
					opstr[j] = s[i];
					j++;
					break;
				case (46): /* this is a '.' */
					opstr[j] = s[i];
					j++;
					break;
				default:
					break;
			}
		}
	}
	verify(opstr);
}

void 
verify(char * s) {
/* verify that the string entered can be evaluated mathematically */
	/* set up some integer indices */
	int i, j;
	
	printf("%s\n",s); /* this is just to help visualize the current state of the string */
	/* next swap all whitespace with spaces */
	spcws(s); 
	printf("%s\n",s); /* show me what it looks like now */
	/* initialize 'len' */
	len = strlen(s);

	for (i = 0; i < len; i++) {
		/* remove consecutive runs of spaces */
		if ((isws(s[i]) == 0) && (isws(s[i+1]) == 0)) { 
			for (j = i+1; (isws(s[j]) == 0) && (s[j] != 0); j++) {
				/* keep incrementing j until we get to the next non-whitespace char */
				;
			}
			/* found at least two spaces */
			/* scan for next non-whitespace character */
			condense(s, (i+1), j, len);
			/* this likely wouldn't be the a terribly efficient solution, but it should give the right results */
		}
	}
}

int 
condense(char * string, int start, int stop, int length) {
	/* shrink the string and recalculate the length */
	char * substr;
	int i, j; /* string iterators */
	if ((substr = (char *) calloc(1,(length - stop + 1) * sizeof(char))) == NULL) {
		printf("ERR: COULDN'T ALLOCATE MEMORY FOR *substr\n");
		return 3;
	}

	for (i = stop,j = 0; string[i] != 0; i++,j++) { 
		/* copy contents of *string into *substr */
		substr[j] = string[i]; 
	}
	/* now let's copy the contents of *substr back into the original string */
	for (i = start,j = 0; substr[j] != 0; i++,j++) { 
		string[i] = substr[j];
	}
	/* change the tracked string length after writing *substr to *string */
	len -= start + stop;
	printf("%s\n",string); /* show me what the string's become */
	/* don't forget to release that memory! */
	free(substr);
	return 0;
}	

int 
isws(char c) {
	/* test to see if the given character is a whitespace character */
	/* returns 0 if it is whitespace, 1 otherwise */
	switch (c) {
		case 9: /* this is a horizontal tab, or '\t' */
			return 0;
		case 11: /* this is a vertical tab, I'm not sure at all what these are used for */
			return 0;
		case 13: /* carriage return, '\r' */
			return 0;
		case 10: /* linefeed, creates a new line */
			return 0;
		case 32: /* space character */
			return 0;
		default: /* not one of the above? not whitespace */
			return 1;
	}
}

/* swap all whitespace characters with a space, ASCII 32 */
void 
spcws(char * s) {
	int i; /* run over the string */
	
	/* swap whitespace chars with spaces */
	for (i = 0; s[i] != 0; i++) { 
		switch (s[i]) {
			case 9 :
				s[i] = 32;
				break;
			case 10 :
				s[i] = 32;
				break;
			case 11 :
				s[i] = 32;
				break;
			case 13 :
				s[i] = 32;
				break;
			default :
				break;
		}
	}
}

/*
 * Exercise 3-4 of K&R's ANSI C 2nd edition
 * found on page 64
 * Meant to modify itoa.c such that it correctly prints 
 * the value of n = -(2^(wordsize - 1))
 * If possible, explain why this doesn't work correctly in the original itoa.c
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* prototype for itoa() */
void itoa(int n, char s[]);
/* 
 * This is not the best solution, but until I can think of something better than a 
 * trap (n = INT_MIN ? s[] = "8463847412-"; break; : n = -n;)
 * though I may be able to cast it to an unsigned int and try reversing it that way
 */
/* prototype for reverse() */
void reverse(char s[]);

/* I'm attempting to conform to the DragonFly BSD style of code */
int main(void){
	char *ostr; /* going to try the pointer method this time around */
	int *input; /* grab an int from the user */
	input = (int *) malloc (sizeof(int)); /* allocate enough space for two ints to be safe */
	ostr = (char *) malloc (4 * sizeof(int)); /* this should be more than sufficient for the resulting string */

	/*prompt the user for a number */
	printf("INT_MIN: %d\n",INT_MIN);
	printf("Enter an integer: ");
	scanf("%d",input); /* hopefully this is being used correctly */
	printf("Captured: %d\n",*input);
	itoa(*input,ostr); /* convert the int to a string */
	printf("\nTranslated to a string: %s\n",ostr);
	/* ideally this will prevent memory leaks */
	free (input);
	free (ostr);
	return 0;
}

/* reverse(), same as mentioned in itoa.c */
void reverse(char s[]){
	int c, i, j; /* placeholders */
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)	{
		c = s[i]; /* grab the value of s[i] */
		s[i] = s[j]; /* put s[j] into s[i] */
		s[j] = c; /* put the stored value of s[i] into s[j] */
	}
}

/* revised version of itoa() */
void itoa(int n, char s[]){
	/* now the magic happens */
	int i, sign;
	/* record if this is a negative number */
	i = 0; /* initialize the counter */
	if ((sign = n) < 0)
		if (n == INT_MIN){
      n = -(n + 1);
      i = -1;
    }
    else{
      n = -n;
    }
		/* n ^= (~n >> 1) << 1; */
	printf("\nCurrent value of 'n': %d\n",n);
		/*
		 * Through some searching, in a a two's complement system, as used with binary representation of numbers
		 * in these programs, the most significant bit (leftmost on little-endian systems), determines the sign
		 * (+/-). This may be possible to correct by doing some bitwise operations such as:
		 * n &= (n >> 2) << 1; (1100 1011 >> 2) << 1 = (0011 00101) << 1 = 0110 1010
		 * which should flip the sign bits and subtract 1 from the positive result
		 */
	
	do {
    if (i == -1){
      s[i+2] = (n % 10) - 1 + '0'; /* this should allow the number value to be calculated correctly */
      i += 2; /* this should put us at the correct point in the string for the next pass */
    }
    else {
		  s[i++] = (n % 10) + '0'; /* if s[i++] = 0 (0); 0 % 10 = 0; 0 + '0' (48) = 48; */
    }
	} while ((n /= 10) > 0); /* keep going as long as 'n' is greater than 10 */

	if (sign < 0)
		s[i++] = '-'; /* or ASCII 45 if you prefer */
	s[i] = 0; /* because ASCII NULL is 0 */
	reverse(s); /* because the number was written backwards initially */
}

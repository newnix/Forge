/*
 * Exercise 3-5 from K&R's ANSI C 2nd edition
 * found on page 64
 * Write a function, itob(n,s,b) that converts integer n
 * to a base b character representation in the string s.
 * For example, itob(15,s,16) would return F
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* prototype for itob */
void itob(int n, char * s, int b); 
/* 
 * take int n, convert it to base b, and write it to string s
 */

int main(void){
	/* do magic */
	int input; /* the number from the user to convert */
	int base; /* the base to convert input into */
	char * output; /* the output string */
	char again; /* loop again? */

	/* allocate some space for the characters */
	/* currently assumes there's enough space in RAM */
	output = (char *) malloc (128 * sizeof(char)); /* should be more than enough for any int */
	again = (char *) malloc (sizeof(char));
	/* and now the numeric inputs */
	input = (int *) malloc (sizeof(int));
	base = (int *) malloc (sizeof(int));

	/* set up a loop to keep going until the user exits */
	for (;;){
		if (upper(again) != 'Y')
			break;
		/* now we print out the fun stuff */
		printf("This will convert a number into another base.\n"
		printf("Please enter an integer:\t");
		scanf("%d",input); /* captured input */
		printf("Please enter a base to convert to:\t",base); /* capture new base */
		itob(*input, output, *base); /* convert the things */
		printf("%d converted to base %d is: %s\n", input, base, output);
		printf("\nWould you like to convert another integer? [Y/N]\n");
		scanf("%c",again);
	}
	/* free the memory to avoid leaks */
	free(input);
	free(base);
	free(again);
	free(output);
	/* this should really be a function clearing an array */
	return 0;
}

void itob(int n, char * s, int b){
	/* number conversion magic */
	/* 
	 * there doesn't appear to be a way to convert by using log(), 
	 * so I'll most likely need to do some sort of recursive division
	 * to get the result I'm looking for
	 */
}

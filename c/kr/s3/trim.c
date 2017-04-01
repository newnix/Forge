/* 
 * This is an example function in K&R's ANSI C 2nd Edition
 * found on page 65. This function trim() is meant to 
 * remove trailing blank characters from a string
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* prototype the function */
int trim(char s[]);

int main(void) {
	/* create a set of variables to use */
	char * input; /* for the user's input */
	int trimrc; /* trim return code */
	
	/* allocate some space for user input */
	if ((input = malloc(1024 * sizeof(char))) == NULL) {
		printf("ERROR: COULD NOT ALLOCATE MEMORY FOR INPUT STRING\n");
		return 3;
	}
	/* grab a string from the user */
	scanf("%s",input);
	trimrc = trim(input);
	printf("The trimmed string: %s\n",input);
	printf("trim() returned: %d\n",trimrc);
	return 0;
}

int trim(char s[]) {
	int n; 

	for (n = strlen(s) - 1; n >= 0; n--) {
		if ((s[n] != ' ') && (s[n] != 9) && (s[n] != '\n')) {
			break;
		}
	}
	s[n + 1] = 0;
	return n; /* This is how many characters we got through before breaking the loop */
}

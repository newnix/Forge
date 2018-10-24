/*
 * This is example code from https://en.wikipedia.org/wiki/Callback_(computer_programming)
 * which is supposed to display the use of callbacks in C
 */

#include <stdio.h>
#include <stdlib.h>

/* 
 * this function takes a function (callback) as its sole parameter
 */
void
print2numbers(int (*source)(void)) {
	int val1 = source();
	int val2 = source();
	printf("%d and %d\n", val1, val2);
}

/* possible callback */
int
over9k(void) {
	return((rand()%1000) + 9001);
}

/* another possible callback */
int
meaningOfLife(void) {
	return(42);
}

/* here we call the function using some available callbacks */
int
main(void) {
	print2numbers(&rand);
	print2numbers(&over9k);
	print2numbers(&meaningOfLife);
	return(0);
}

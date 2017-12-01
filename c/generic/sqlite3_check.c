#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int 
main(void) {
	long int threaded;

	threaded = 0;

	threaded = sqlite3_threadsafe();

	if (threaded == 1) {
		(void)fprintf(stdout,"sqlite3 is thread safe\n");
	} else {
		(void)fprintf(stdout,"sqlite3 is not thread safe\n");
	}

	return 0;
}

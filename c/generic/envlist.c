/*
 * This binary should just print the environmental 
 * variables in **environ, and exits
 */

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int
main(void) {
	int envp;

	for (envp = 0; environ[envp] != NULL; envp++) {
		fprintf(stdout, "%p\t%s\n", environ[envp], environ[envp]);
	}

	fprintf(stdout,"\nRead %d environmental variables\n", envp);
	return(0);
}

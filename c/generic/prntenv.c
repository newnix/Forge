/*
 * This is meant as a simple way to print environmental variables
 * mostly as an exercise in getting variables that are exposed to the 
 * programs launched via CLI
 */

#include <stdio.h>
#include <stdlib.h>

int 
main(char **envp){
	/* set up a couple of vars to use */
	char **env;

	for(env = envp; *env !=0; env++){
		char *thisEnv = getenv(*env) ;
		printf("%s\n", thisEnv);
	}
	return 0;
}

/*
 * This binary should just print the environmental 
 * variables in **environ, and exits
 *
 * Literally a reimplemented env(1), with fewer features
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>

extern char **environ;

int
main(void) {
	int envp;
	unsigned int uid, euid;
	char *homedir, *username;

	uid = euid = 0;
	uid = getuid();
	euid = geteuid();
	homedir = getenv("HOME");
	username = getenv("USER");

	fprintf(stdout, "Reading environmental data for UID: %u, EUID: %u...\n",uid, euid);
	fprintf(stdout, "Username: %s\n$HOME: %s\n",username, homedir);
	for (envp = 0; environ[envp] != NULL; envp++) {
		fprintf(stdout, "%p\t%s\n", &environ[envp], environ[envp]);
	}

	/* 
	 * There used to be a sizeof(environ) call here, to show the 
	 * number of entries allocated, but it would always return 8. 
	 * This is due to the size of **environ being 8bytes on a 
	 * 64-bit machine, like all pointers. If this were run on 
	 * a 32-bit machine, I would expect sizeof(environ) to return 4.
	 */
	fprintf(stdout,"\nRead %d environmental variables\n", envp);
	return(0);
}

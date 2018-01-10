/*
 * This binary should just print the environmental 
 * variables in **environ, and exits
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
		fprintf(stdout, "%p\t%s\n", environ[envp], environ[envp]);
	}

	fprintf(stdout,"\nRead %d environmental variables\n", envp);
	return(0);
}

/*
 * This binary should just print the environmental 
 * variables in **environ, and exits
 *
 * Literally a reimplemented env(1), with fewer features
 */

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


extern char **environ;

/* some prototypes */
void envwalk(void);
void run_help(void);
int senv(char *variable, char *value);
int delenv(char *env);

int
main(int argc, char **argv) {
	int list, set, unset, ch;
	char *env;
	char *variable, *value;

	ch = list = set = unset = 0;
	
	while ((ch = getopt(argc, argv, "d:hls:v:")) != 1) {
		switch (ch) {
			case 'd':
				unset = 1;
				env = calloc(65535,1);
				strncpy(env, optarg, 65535);
				break;
			case 'h':
				run_help();
				return(0);
			case 'l':
				list = 1;
				break;
			case 's':
				set = 1;
				variable = calloc(65535,1);
				strncpy(variable,optarg,65535);
				break;
			case 'v':
				if (set == 0) {
					break;
				} else {
					value = calloc(65535,1);
					strncpy(value,optarg,65535);
					break;
				}
			default:
				break;
		}
	}
	if (set == 1) {
		senv(variable,value);
	}
	if (unset == 1) {
		delenv(env);
	}
	if (list == 1) {
		envwalk();
	}
	return(0);
}

/* create new setenv() functions */
int
delenv(char *env) {
	return(unsetenv(env));
}

void
run_help(void) {
	fprintf(stdout,"basic reimplementation of the env(1) utility\n");
}

int
senv(char *variable, char *value) {
	return(setenv(variable, value, 1));
}	

void
envwalk(void) {
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
}

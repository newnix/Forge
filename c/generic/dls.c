/* 
 * This is meant to re-implement the basic utility of
 * ls(1), to provide practice with directory traversal
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <fts.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
extern char *__progname;

/* Function prototyping */
void run_help(void);
int dls(char *target);
int scan_args(int argsize, char **arglist);

int
main(int argc, char **argv) { 
	int i, newline, ch;

	i = ch = newline = 0;
	/* here we need to determine what sort of flags are going to be used */
	fprintf(stdout,"Argv list:\n");
	for (i = 0; i < argc; i++) { 
		fprintf(stdout,"argc[%d]: %s\n", i, argv[i]);
	}
	while ((ch = getopt(argc, argv, "h1")) != -1) {
		switch(ch) {
			case 'h':
				run_help();
				break;
			case '1':
				newline=1;
				break;
			default:
				/* this does not get run if the user provides no flags */
				fprintf(stdout,"ch = %d\n",ch);
				break;
		}
	}
	/* now actually look for directories to walk through */
	scan_args(argc, argv);
	return(0);
}

void
run_help(void) { 
	/* print out the usage info */
	fprintf(stdout,"Minimal reimplementation of ls(1)\n");
}

int
dls(char *target) {
	fprintf(stdout,"Listing contents of %s\n:",target);
	return(0);
}

int
scan_args(int argsize, char **arglist) { 
	int i; 
	
	/* argv[0] is always *__progname */
	for (i = 1; i < argsize; i++) { 
		fprintf(stdout,"arglist[%d] = %s\n",i, arglist[i]);
		fprintf(stdout,"arglist[%d][0] = %c\n", i, arglist[i][0]);
		/* assume anything not proceeded by a '-' is a directory */
		if (arglist[i][0] == '-') { 
			/* do nothing */
		} else { 
			dls(arglist[i]);
		}
	}
	return(0);
}

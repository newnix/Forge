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
int prntent(FTSENT *entry);

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
				return(0);
			case '1':
				newline=1;
				break;
			default:
				break;
		}
	}
	/* now actually look for directories to walk through */
	return(scan_args(argc, argv));
}

int
dls(char *target) {
	FTS *ftsp;
	FTSENT *entry;
	fprintf(stdout,"Listing contents of %s\n:",target);
	ftsp = fts_open(&target, FTS_COMFOLLOW | FTS_SEEDOT,0);
	entry = fts_read(ftsp);
	if (entry != NULL) {
		prntent(entry);
	} else { 
		return(-1);
	}
	return(0);
}

int
prntent(FTSENT *entry) {
	fprintf(stdout,"fts_info:    %d\n",entry->fts_info);
	fprintf(stdout,"fts_accpath: %s\n",entry->fts_accpath);
	fprintf(stdout,"fts_path:    %s\n",entry->fts_path);
	fprintf(stdout,"filename:    %s\n",entry->fts_name);
	fprintf(stdout,"fts_number:  %lld\n",entry->fts_number);
	fprintf(stdout,"fts_pointer: %p\n",entry->fts_pointer);
	return(0);
}

void
run_help(void) { 
	/* print out the usage info */
	fprintf(stdout,"Minimal reimplementation of ls(1)\n");
	fprintf(stdout,"\t-h\tThis text\n");
	fprintf(stdout,"\t-1\tList one entry per line\n");
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
			if (dls(arglist[i]) == -1) {
				return(-1);
			}
		}
	}
	return(0);
}

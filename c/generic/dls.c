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
int dbg;

/* Function prototyping */
void run_help(void);
int dls(char **target);
int scan_args(int argsize, char **arglist);
int prntent(FTSENT *entry);

int
main(int argc, char **argv) { 
	int i, newline, ch;

	dbg = 0;
	i = ch = newline = 0;
	/* here we need to determine what sort of flags are going to be used */
	fprintf(stdout,"Argv list:\n");
	for (i = 0; i < argc; i++) { 
		fprintf(stdout,"argc[%d]: %s\n", i, argv[i]);
	}
	while ((ch = getopt(argc, argv, "dh1")) != -1) {
		switch(ch) {
			case 'd':
				dbg=1;
				break;
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

/* 
 * This function will end up passing duplicate values to 
 * prntent(). This will need to be fixed somehow, possibly by 
 * adding the entries to an array somewhere or possibly by 
 * adding another case statement to the loop reading the fts
 * entries. Will need to consult documentation and the ls(1) 
 * source code to be certain what the best course of action is.
 */
int
dls(char **target) {
	FTS *ftsp;
	FTSENT *entry;
	fprintf(stdout,"Listing contents of %s\n:",*target);
	if ((ftsp = fts_open(target, FTS_PHYSICAL | FTS_COMFOLLOW | FTS_SEEDOT,0)) == NULL) {
		err(1,"fts_open");
		return(-1);
	}

	while ((entry = fts_read(ftsp)) != NULL) {
		switch(entry->fts_info) {
			case FTS_DC:
				fprintf(stdout,"%s: Directory leads to cyclical tree!\n",entry->fts_name);
				break;
			case FTS_DNR:
				err(1,"fts_read");
				return(-1);
			case FTS_ERR:
				fprintf(stderr,"%s : %s",entry->fts_name,strerror(entry->fts_errno));
				return(-1);
			default:
				prntent(entry);
		}
	}
	fts_close(ftsp);
	return(0);
}

int
prntent(FTSENT *entry) {
	if (dbg) { 
		if (entry->fts_level > 1) { 
			return(0);
		} else { 
			fprintf(stdout,"fts_accpath: %s\n",entry->fts_accpath);
			fprintf(stdout,"fts_path:    %s\n",entry->fts_path);
			fprintf(stdout,"filename:    %s\n",entry->fts_name);
			fprintf(stdout,"fts_level:  %ld\n",entry->fts_level);
			return(0);
		}
	} else { 
		if (entry->fts_level == 1) { 
			fprintf(stdout,"%s\n",entry->fts_path);
			return(0);
		} else { 
			return(0);
		}
	}
}

void
run_help(void) { 
	/* print out the usage info */
	fprintf(stdout,"Minimal reimplementation of ls(1)\n");
	fprintf(stdout,"\t-d\tDisplay debugging (struct) info\n");
	fprintf(stdout,"\t-h\tThis text\n");
	fprintf(stdout,"\t-1\tList one entry per line\n");
}

int
scan_args(int argsize, char **arglist) { 
	int i; 
	
	/* argv[0] is always *__progname */
	for (i = 1; i < argsize; i++) { 
	/*
		fprintf(stdout,"arglist[%d] = %s\n",i, arglist[i]);
		fprintf(stdout,"arglist[%d][0] = %c\n", i, arglist[i][0]);
	 */
		/* assume anything not proceeded by a '-' is a directory */
		if (arglist[i][0] == '-') { 
			/* do nothing */
		} else { 
			dls(&arglist[i]);
		}
	}
	return(0);
}

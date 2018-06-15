/* 
 * This file simply contains function definitions for those found in nxls.c
 */

#ifndef __NXLS_H__
#define __NXLS_H__

/* ensure we have limits */
#include <limits.h>

/* enumerated pass-to targets */
enum passtarget { XLS, ALPHASORT, SIZESORT, DOTSTRIP, STATDATA, FSAPPEND };

/*
 * function signatures
 */
static int buildlist(struct dirent *entry, enum passtarget passto);
static int targets(char **arglist, uint16_t flags);
static void __attribute__((noreturn)) usage(void);
static int xls(char **contents);

/* 
 * define directory symbols 
 */
#define DIRECTORY '/'
#define SYMLINK '@'
#define HARDLINK "->"
#define EXECUTABLE '*'

/* 
 * Simple interface, simply add the d_name values to a list per-directory
 * each new directory should trigger this array being reset
 * pass the array to xls() if pass == 1
 */
static int
buildlist(struct dirent *entry, enum passtarget passto) {
	char **contents;
	static int i = 0;

	if (passto == XLS) { 
		xls(contents);
	}

	if ((contents = calloc(PATH_MAX,PATH_MAX)) == NULL) { 
		return(-1);
	}

	/* copy the dirent name to the next slot */
	if (strlcpy(contents[i],entry->d_name,PATH_MAX) != 0) {
		i++;
		return(0);
	} else {
		return(-1);
	}
	xls(contents);
}

static int
targets(char **arglist, uint16_t flags) {
	/* allocate space for a stat(2) struct */
	DIR *dirp;
	struct dirent *entry;
	struct stat *ent;

	dirp = NULL;
	entry = NULL;

	if ((ent = calloc(1,sizeof(*ent))) == NULL) { 
			return(1);
	}
	/* if no arguments were given, list PWD */
	if (*arglist == NULL) { 
		if ((dirp = opendir(".")) != NULL) {	
			while ((entry = readdir(dirp)) != NULL) { 
				buildlist(entry);
			}
		}
	}
	for (; *arglist != NULL; arglist++) {
		/* 
		 * So, instead of running through everything, let's just get a map of the entities in 
		 * a given directory, and pass that to xls(), which in turn will determine if there's any further action 
		 * needed prior to printing the entries.
		 */
		if (((dirp = opendir(*arglist)) != NULL) && (chdir(*arglist) == 0)) { 
			while ((entry = readdir(dirp)) != NULL) {
				buildlist(entry);
			}
		} else {
			err(errno,"%s",*arglist);
		}
	}
	if (dirp != NULL) {
		closedir(dirp);
	}
	free(ent);
  return(0);
}

static void __attribute__((noreturn))
usage(void) {
	/* changed from fprintf() to write(), should save size and perform a bit faster */
	char *usage = "nxls: New Exile's ls(1)\n\
	nxls [-aflrFHS1] [file ...]\n\n\
	-a  Include dotfiles\n\
	-f  Print absolute paths\n\
	-h  This message\n\
	-l  Longer output\n\
	-r  Recursive listing\n\
	-s  Sort by size\n\
	-F  Append filetype symbols\n\
	-A  Alphabetical sort\n\
	-H  Human friendly sizes\n\
	-S  Stat struct info\n\
	-1  One entry per line\n";
	write(1,usage,strlen(usage));
	exit(0);
}

/* display the entries, pontentially after sorting them */
static int
xls(char **contents) { 
	/* this will now only take an object/struct to display */
	for (; *contents != NULL; *contents++) {
		fprintf(stdout,"%s\n",*contents);
	}
	return(0);
}

#endif

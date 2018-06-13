/* 
 * This file simply contains function definitions for those found in nxls.c
 */

#ifndef __NXLS_H__
#define __NXLS_H__
/*
 * function signatures
 */
static int targets(char **arglist, uint16_t flags);
static void __attribute__((noreturn)) usage(void);
static int xls(const char *name, uint16_t flags);

/* 
 * define directory symbols 
 */
#define DIRECTORY '/'
#define SYMLINK '@'
#define HARDLINK "->"
#define EXECUTABLE '*'

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
				xls(entry->d_name,flags);
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
			while ((entry = readdir(dirp)) != NULL && (xls(entry->d_name,flags)) != 0) { 
				;
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
	-F  Append filetype symbols\n\
	-H  Human friendly sizes\n\
	-S  Stat struct info\n\
	-1  One entry per line\n";
	write(1,usage,strlen(usage));
	exit(0);
}

/* 
 * add targets to a struct array? 
 * an arry of structs? perhaps?
 * linked list?
 */
static int
xls(const char *name, uint16_t flags) { 
	/* for the time being, just spit out the dirent names to stdout */
	return(buildlist(name));
}

#endif

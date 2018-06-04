/* 
 * Copyright (c) 2017-2018, Exile Heavy Industries
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without specific
 *   prior written permission.
 * 
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
 * LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */ 

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>

#include <dirent.h> 
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h> /* so linux can build with uint16_t */
#include <stdlib.h>
#include <string.h>

extern char **environ;
extern char *__progname;

/* Function prototypes */
static void __attribute__((noreturn)) usage(void);
static int targets(char **arglist);
/* Perhaps this should build a map of some sort, collecting the entries and stat(2) structure pointers */
static int xls(const char *name);

#define ALLFILES 0x01
#define FULLPATH 0x02
#define HELPFLAG 0x00
#define LONGLIST 0x04
#define RECURSIV 0x08
#define HUMANSIZ 0x10
#define FILESYMB 0x20
#define STATINFO 0x40
#define ONELINE  0x80

int
main(int argc, char **argv) { 
  int opt;
	uint16_t flags;

  flags = opt = 0;

  while ((opt = getopt(argc, argv, "afhrFHS1")) != -1) {
    switch(opt) {
			case 'a': /* include dotfiles */
				flags ^= ALLFILES;
				break; /* not currently implemented */
      case 'f': /* print full path instead of relative path */
				flags ^= FULLPATH;
        break; /* not currently implemented */
      case 'h': /* help */
				flags &= HELPFLAG;
        usage();
			case 'l': /* longer output */
				flags ^= LONGLIST;
				break; /* not currently implemented */
			case 'r': /* recursive */
				flags ^= RECURSIV;
				break; /* not currently implemented */
			case 'H': /* human friendly sizes */
				flags ^= HUMANSIZ;
				break; /* not currently implemented */
      case 'F': /* append filetype symbols, like in 'ls -F' */
				flags ^= FILESYMB;
        break; /* not currently implemented */
      case 'S': /* full stat(2) struct info */
				flags ^= STATINFO;
        break; /* not currently implemented */
      case '1': /* exactly one entry per line */
				flags &= ONELINE;
        break; /* not currently implemented */
      default:
        break;
    }
  }

	argc -= optind;
	argv += optind;
	targets(argv);
  return(0);
}

static int
targets(char **arglist) {
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
				xls(entry->d_name);
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
				xls(entry->d_name);
			}
		} else {
			err(errno,"chdir");
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
xls(const char *name) { 
	/* for the time being, just spit out the dirent names to stdout */
	fprintf(stdout,"%s\n",name);
	return(0);
}

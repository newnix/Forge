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
/* apparently this is significantly different than using FTS */
static int xls(struct stat *entry, const char *name);

int
main(int argc, char **argv) { 
  int opt;

  opt = 0;

  while ((opt = getopt(argc, argv, "afhrFHS1")) != -1) {
    switch(opt) {
			case 'a': /* include dotfiles */
				break; /* not currently implemented */
      case 'f': /* print full path instead of relative path */
        break; /* not currently implemented */
      case 'h': /* help */
        usage();
			case 'l': /* longer output */
				break; /* not currently implemented */
			case 'r': /* recursive */
				break; /* not currently implemented */
			case 'H': /* human friendly sizes */
				break; /* not currently implemented */
      case 'F': /* append filetype symbols, like in 'ls -F' */
        break; /* not currently implemented */
      case 'S': /* full stat(2) struct info */
        break; /* not currently implemented */
      case '1': /* exactly one entry per line */
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
	for (; *arglist != NULL; arglist++) {
		/* 
		 * This is going to be reworked for the readdir(3) function
		 * instead of nftw(3)
		 */
		if (((dirp = opendir(*arglist)) != NULL) && (chdir(*arglist) == 0)) { 
			while ((entry = readdir(dirp)) != NULL) { 
				/* 
				 * there's a few interesting items in the dirent struct, but the only one we can't get 
				 * through the stat struct is th ename of the file, which feels a bit dumb, but 
				 * probably has its uses
				 */
				if (lstat(entry->d_name,ent) == 0) { 
					/* this, of course, needs to be handled better */
					fprintf(stdout,"%s\n",entry->d_name);
					xls(ent,entry->d_name);
				} else { 
					err(errno,"stat(%s)",entry->d_name);
				}
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

static int
xls(struct stat *entry, const char *name) { 
	/* this should prevent listing recursively by default */
	return(0);
}

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

/* this is necessary for nftw(3) to work on linux for some reason */
#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h> /* may not be necessary, not sure yet */
#include <err.h>
#include <errno.h>
#include <ftw.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h> /* so linux can build with uint16_t */
#include <stdlib.h>
#include <string.h>

extern char **environ;
extern char *__progname;

/* Function prototypes */
static void __attribute__((noreturn)) run_help(void);
static int scan_args(char **arglist);
/* apparently this is significantly different than using FTS */
static int xls(const char *target, const struct stat *info, int i, struct FTW *ftw);

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
        run_help();
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
	scan_args(argv);
  return(0);
}

static void
run_help(void) {
  fprintf(stdout,"%s: New Exile's ls(1)\n",__progname);
	fprintf(stdout,"\t-a\tinclude dotfiles\n");
	fprintf(stdout,"\t-f\tPrint absolute path instead of relative path\n");
  fprintf(stdout,"\t-h\tThis help text\n");
	fprintf(stdout,"\t-l\tLonger output\n");
	fprintf(stdout,"\t-r\tRecursive listing\n");
  fprintf(stdout,"\t-F\tAppend filetype symbols\n");
	fprintf(stdout,"\t-H\tHuman friendly file sizes\n");
  fprintf(stdout,"\t-S\tstat(2) struct info\n");
  fprintf(stdout,"\t-1\tOne entry per line\n");
	exit(0);
}

static int
scan_args(char **arglist) {
	/* if no arguments were given, list PWD */
	if (*arglist == NULL) {
		if (nftw(getenv("PWD"), &xls, 10, (FTW_PHYS | FTW_DEPTH)) == -1) {
			perror("nftw");
		}
	}
	for (; *arglist != NULL; arglist++) {
		/* 
		 * I'm not sure if there's an argument that needs to be passed here or
		 * if xls() needs to detect when we change into a new directory and return 
		 * a nonzero value in that circumstance to prevent the recursive listing
		 * seen currently 
		 *
		 * There should be a way to ensure we don't automatically recurse
		 */
		if (nftw(*arglist, &xls, 10, (FTW_PHYS)) == -1) {
			perror("nftw");
		}
	}
  return(0);
}

static int
xls(const char *target, const struct stat *info, int i, struct FTW *ftw) { 
	/* this should prevent listing recursively by default */
	if (i == FTW_D) { return(0); } 
	fprintf(stdout,"i = %d\t%s\n",i, target);
	if (ftw->level < 2) {
		fprintf(stdout,"stat(2) struct info for %s:\n",target);
		fprintf(stdout,"st_ino:\t\t%lu\t\tst_nlink:\t%u\n",info->st_ino, info->st_nlink);
		fprintf(stdout,"st_dev:\t\t%u\tst_mode:\t%o\n",info->st_dev, info->st_mode);
		fprintf(stdout,"st_uid:\t\t%d\t\tst_gid:\t\t%d\n",info->st_uid, info->st_gid);
		fprintf(stdout,"st_size:\t%ld\t\tst_blocks:\t%ld\n",info->st_size, info->st_blocks);
		fprintf(stdout,"st_blksize:\t%u\n",info->st_blksize);
		fprintf(stdout,"ftw->base:\t%d\t\tftw->level:\t%d\n",ftw->base, ftw->level);
	}
	return(0);
}

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

/* 
 * This is currently just a redo of dls.c, but using ftw(3) 
 * instead of the non-portable fts(3). It may eventually be replaced 
 * with a cleaner, better written version for the nxu project.
 * As that is meant to be a mostly feature-complete replacement
 * for the coreutils.
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <ftw.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
extern char *__progname;
int dbg;

/* Function prototypes */
void run_help(void);
int scan_args(char **arglist);
/* apparently this is significantly different than using FTS */
int xls(char *target, const struct stat *info, struct FTW *ftw);

int
main(int argc, char **argv) { 
  int opt;

  opt = 0;

  while ((opt = getopt(argc, argv, "fhS1")) != -1) {
    switch(opt) {
      case 'f': 
        break; /* not currently implemented */
      case 'h':
        run_help();
        return(0);
      case 'S':
        break; /* not currently implemented */
      case '1':
        break; /* not currently implemented */
      default:
        break;
    }
  }
	scan_args(argv);
  return(0);
}

void
run_help(void) {
  fprintf(stdout,"%s: New Exile's ls(1)\n",__progname);
  fprintf(stdout,"\t-h\tThis help text\n");
  fprintf(stdout,"\t-f\tFull struct info\n");
  fprintf(stdout,"\t-S\tstat(2) struct info\n");
  fprintf(stdout,"\t-1\tOne entry per line\n");
}

int
scan_args(char **arglist) {
	int i;
	/*
	 * We assume that any argument not starting with '-' 
	 * is a target for us to display
	 *
	 * Since argv[0] is always __progname, start counting from 1
	 */
	for (i = 1; arglist[i] != NULL; i++) { 
		if (arglist[i][0] != '-') {
			if (nftw(arglist[i], xls, 10, FTW_PHYS) == -1) {
				perror("nftw");
			}
		} else { 
			break;
		}
	}
  return(0);
}

int
xls(char *target, const struct stat *info, struct FTW *ftw) { 
	/* pubs.opengroup.org has some good documentation for this */
	fprintf(stdout,"stat(2) struct info for %s:\n",target);
	fprintf(stdout,"st_ino:\t%lu\nst_nlink:\t%u\n",info->st_ino, info->st_nlink);
	fprintf(stdout,"st_dev:\t%u\nst_mode:\t%o\n",info->st_dev, info->st_mode);
	fprintf(stdout,"st_uid:\t%d\nst_gid:\t%d\n",info->st_uid, info->st_gid);
	fprintf(stdout,"st_size:\t%ld\nst_blocks:\t%ld\n",info->st_size, info->st_blocks);
	fprintf(stdout,"st_blksize:\t%u\n",info->st_blksize);
	return(0);
}

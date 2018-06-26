/*
 * Copyright (c) 2018, Exile Heavy Industries
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
 * this is meant to be a simple program to walk the VFS layer of a *BSD
 * system, hopefully this will be mostly portable to systems other
 * than DragonFly BSD, but since the VFS layer is different on each OS,
 * that may not be feasible. 
 * Output should be similar to calling mount(8) without any arguments
 */

/* system includes */
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <sys/ucred.h>

/* userspace includes */
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "vfswalk.h"
/* ensure the environment's accessible */
extern char *__progname;

static void __attribute__((noreturn)) usage(void);
void fsprint(struct statfs *fsbuf);
static int vfsinfo(char *mountpoint);
static int vfswalk(void);
void vfsprint(struct statvfs *vfsbuf);

int
main(int argc, char **argv) {
	if (argv[1] != NULL && strncmp(argv[1],"help",(size_t)5) == 0) { 
		usage();
	} 

	if (argv[1] != NULL) { 
		for (++argv; *argv != NULL; argv++) { 
			vfsinfo(*argv);
		}
		return(0);
	}
	return(vfswalk());
}

static void 
__attribute__((noreturn)) usage(void) {
	fprintf(stderr,"%s: Simple tool to pull VFS info\n"
			           "\t%s help: this text\n"
								 "\t%s /home: VFS info of mountpoint /home\n",
								 __progname,__progname,__progname);
	exit(0);
}

/*
 * this function will print the statfs and statvfs struct information 
 * for a given mountpoint
 */
static int
vfsinfo(char *mountpoint) {
	struct statvfs *vfsbuf;
	struct statfs *fsbuf;

	if ((fsbuf = calloc(sizeof(*fsbuf),1)) == NULL) { 
		return(-1);
	}

	if ((vfsbuf = calloc(sizeof(*vfsbuf),1)) == NULL) { 
		return(-1);
	}

	if (statvfs(mountpoint, vfsbuf) == 0) { 
		fprintf(stdout,"statvfs struct info for %s:\n", mountpoint);
		vfsprint(vfsbuf);
		free(vfsbuf);
	} else { 
		err(errno,"%s: ", mountpoint);
		free(vfsbuf);
	}

	if (statfs(mountpoint, fsbuf) == 0) { 
		fprintf(stdout,"\nstatfs struct info for %s:\n", mountpoint);
		fsprint(fsbuf);
		free(fsbuf);
	} else { 
		err(errno,"%s: ", mountpoint);
		free(fsbuf);
	}
	return(0);
}

/*
 * Display info on every currently mounted filesystem
 */
static int
vfswalk(void) { 
	struct statfs *fsbuf;
	struct statvfs *vfsbuf;
	long vfsbufsize;
	int flags, fscount;

	vfsbufsize = 0;
	flags = MNT_WAIT;
	fscount = 0;
	fsbuf = NULL; /* use this to get the number of filesystems available */

	if ((fscount = getfsstat(fsbuf,vfsbufsize,flags)) > 0) {
		fprintf(stdout,"%d filesystems mounted, allocating space to display stats...\n",fscount);
		if ((fsbuf = calloc(sizeof(struct statfs *),fscount)) == NULL) {
			return(-1);
		}

		if ((vfsbuf = calloc(sizeof(struct statvfs *),1)) == NULL) {
			return(-1);
		}
		vfsbufsize = (sizeof(*fsbuf) * fscount);
	}
	
	if ((fscount = getfsstat(fsbuf, vfsbufsize, flags)) != -1) { 
		for (flags = 0; flags < fscount; flags++) {
			fprintf(stdout,"\ninfo for %s:\n",fsbuf[flags].f_mntonname);
			fsprint(&fsbuf[flags]);
			if (statvfs(fsbuf[flags].f_mntonname,vfsbuf) == 0) {
				vfsprint(vfsbuf);
			}
		}
	} else {
		err(errno,"getfsstat: ");
	}

	free(fsbuf);
	free(vfsbuf);
	return(0);
}

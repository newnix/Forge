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

/* ensure the environment's accessible */
extern char **environ;
extern char *__progname;

static void __attribute__((noreturn)) usage(void);
static void fsprint(struct statfs *fsbuf);
static int vfsinfo(char *mountpoint);
static int vfswalk(void);
static void vfsprint(struct statvfs *vfsbuf);

int
main(int argc, char **argv) {
	if (geteuid() != 0) { 
		fprintf(stderr,"Warning, %s may require root privileges!\n",__progname);
	}

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

static void
fsprint(struct statfs *fsbuf) { 
	fprintf(stdout,"f_bsize: %ld\tf_iosize: %ld\tf_blocks: %ld\n"
		           "f_bfree: %ld\tf_bavail: %ld\tf_files: %ld\n"
							 "f_ffree: %ld\tf_fsid: %d %d\tf_owner: %u\n"
							 "f_type: %d\tf_flags: %d\tf_syncwrites: %ld\n"
							 "f_asyncwrites: %ld\tf_fstypename: %s\tf_mntonname: %s\n"
							 "f_syncreads: %ld\tf_asyncreads: %ld\tf_mntfromname: %s\n\n",
							 fsbuf->f_bsize,fsbuf->f_iosize,fsbuf->f_blocks,
							 fsbuf->f_bfree,fsbuf->f_bavail,fsbuf->f_files,
							 fsbuf->f_ffree,fsbuf->f_fsid.val[0],fsbuf->f_fsid.val[1],fsbuf->f_owner,
							 fsbuf->f_type,fsbuf->f_flags,fsbuf->f_syncwrites,
							 fsbuf->f_asyncwrites,fsbuf->f_fstypename,fsbuf->f_mntonname,
							 fsbuf->f_syncreads,fsbuf->f_asyncreads,fsbuf->f_mntfromname);
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

static void
vfsprint(struct statvfs *vfsbuf) { 
	fprintf(stdout,"f_bsize: %lu\tf_frsize: %lu\tf_blocks: %lu\n"
		           "f_bfree: %lu\tf_bavail: %lu\tf_files: %lu\n"
							 "f_ffree: %lu\tf_favail: %lu\tf_fsid: %lu\n"
							 "f_flag: %lu\tf_namemax: %lu\tf_owner: %u\n"
							 "f_type: %u\nf_syncreads: %lu\tf_syncwrites: %lu\n"
							 "f_asyncreads: %lu\tf_asyncwrites: %lu\n",
							 vfsbuf->f_bsize,vfsbuf->f_frsize,vfsbuf->f_blocks,vfsbuf->f_bfree,
							 vfsbuf->f_bavail,vfsbuf->f_files,vfsbuf->f_ffree,vfsbuf->f_favail,
							 vfsbuf->f_fsid,vfsbuf->f_flag,vfsbuf->f_namemax,vfsbuf->f_owner,
							 vfsbuf->f_type,vfsbuf->f_syncreads,vfsbuf->f_syncwrites,vfsbuf->f_asyncreads,
							 vfsbuf->f_asyncwrites);
}

/*
 * This should, if I'm reading the manual pages properly, return information on
 * ALL currently mounted filesystems, which will allow me to better investigate 
 * the struct values, though from the working vfsinfo() function, 
 * it looks like HAMMER2 filesystems are identified as fsbuf->f_type == 9
 */
static int
vfswalk(void) { 
	struct statfs *fsbuf;
	struct statvfs *vfsbuf;
	long vfsbufsize;
	int flags, fscount;

	vfsbufsize = 0;
	flags = fscount = 0;

	if (((vfsbuf = calloc(sizeof(vfsbuf),1))) == NULL) { 
		return(-1);
	}

	if (((fsbuf = calloc(sizeof(fsbuf),1))) == NULL) { 
		return(-1);
	}

	if ((fscount = getvfsstat(fsbuf, vfsbuf, vfsbufsize, flags)) != -1) { 
		fprintf(stdout,"getvfsstat returned %d filesystems\n",fscount);
		fprintf(stdout,"statfs struct info:\n");
		fprintf(stdout,"statvfs struct info:\n");
		vfsprint(vfsbuf);
	}

	free(fsbuf);
	free(vfsbuf);
	return(0);
}

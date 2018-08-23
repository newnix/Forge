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
 * this is meant to be a simple tool for locating and destroying HAMMER2 PFS-es
 * that may or may not have been created during the testing of dfbeadm
 */
#include <sys/mount.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <vfs/hammer2/hammer2_disk.h>
#include <vfs/hammer2/hammer2_ioctl.h>

static int fswalk(char *label);
static int h2lookup(char *label, char *fs);
static int h2destroy(struct hammer2_ioc_pfs *pfs, int pfsd);
static int list(void);
static void __attribute__((noreturn)) usage(void);

extern char **environ;
extern bool noconfirm=false;
extern char *__progname;

int
main(int ac, char **av) {
	int ch;

	ch = 0;

	while((ch = getopt(ac, av, "hly")) != -1) {
		switch(ch) {
			case 'h':
				usage();
			case 'l':
				return(list());
			case 'y':
				noconfirm = true;
				break;
			default:
				usage();
		}
	}

	ac -= optind;
	av += optind;

	for(; *av != NULL; av++) {
		if (fswalk(*av) < 0) {
			break;
		}
	}
	return(0);
}

/* 
 * This function loops through the mounted filesystems, examining 
 * HAMMER2 filesystems for the given labels to destroy
 */
static int
fswalk(char *label) {
	struct statfs *fsbuf;
	long fsbufsize;
	int flags, fscount;

	fsbuf = NULL;
	fsbufsize = 0;
	fscount = 0;
	flags = MNT_WAIT;

	if ((fscount = getfsstat(fsbuf, fsbufsize, flags)) > 0) { 
		fprintf(stdout, "Fonud %d filesystems to search through...\n", fscount);
	} 
	/* use the results from the previous call to allocate the necessary buffer size */
	if ((fsbuf = calloc(fscount, sizeof(struct statfs *))) == NULL) {
		fprintf(stderr, "Unable to allocate space for FS buffer!\n");
		return(-1);
	}
	fsbufsize = (sizeof(*fsbuf) * (fscount * 2));
	if (getfsstat(fsbuf, fsbufsize, flags) < 0) { 
		fprintf(stderr, "something went wrong, bailing out\n");
		free(fsbuf);
		return(-2);
	} 

	for (flags = 0; flags < fscount; flags++) {
		fprintf(stderr,"Checking %s...\n",fsbuf[flags].f_mntonname); 
		if (strcmp(fsbuf[flags].f_fstypename, "hammer2") == 0) {
			h2lookup(label, fsbuf[flags].f_mntonname);
		} else {
			fprintf(stdout, "%s is not a HAMMER2 filesystem, skipping...\n", fsbuf[flags].f_mntonname);
		}
	}
	free(fsbuf);
	return(0);
}

/* 
 * this function should act similarly to the loop for `hammer2 pfs-list`
 * though notably, would check for the label provided in the pfs name,
 * and if found, will pass it off to h2destroy()
 */
static int
h2lookup(char *label, char *fs) {
	struct hammer2_ioc_pfs dpfs; /* holds the PFS data to be destroyed */
	int lpfsd; /* file descriptor for the filesystem being searched through */
	
	if((lpfsd = open(fs, O_RDONLY)) < 0) {
		fprintf(stderr,"Unable to open %s\n",fs);
		return(-1);
	}

	memset(&dpfs, 0, sizeof(dpfs));
	for(; dpfs.name_key != (hammer2_key_t)-1; dpfs.name_key = dpfs.name_next) {
		if(ioctl(lpfsd, HAMMER2IOC_PFS_GET, &dpfs) < 0) {
			fprintf(stderr, "Unable to read PFS data in %s\n", fs);
			return(2);
		}
		if(strnstr(dpfs.name, label, NAME_MAX) == NULL) {
			/* do nothing */
		} else {
			if(noconfirm) {
				if(ioctl(lpfsd, HAMMER2IOC_PFS_DELETE, &dpfs) < 0) {
					fprintf(stderr, "Unable to delete %s\n", dpfs.name);
				}
			} else {
				fprintf(stderr, "You're about to destroy %s, this CANNOT be undone, continue? [y/N]: ", dpfs.name);
				fpurge(stdin);
				if((fgetc(stdin) & 223) == 'Y') {
					if(ioctl(lpfsd, HAMMER2IOC_PFS_DELETE, &dpfs) < 0) {
						fprintf(stderr, "Unable to delete %s\n", dpfs.name);
					}
				} else {
					fprintf(stdout, "Skipping matching PFS: %s\n", dpfs.name);
				}
			}
		}
	}
						
	close(lpfsd);
	return(0);
}

/* this simply takes arguments to pass off to the destruction ioctl */
static int 
h2destroy(struct hammer2_ioc_pfs *pfs, int pfsd) {
	return(0);
}

/*
 * List PFSes found in the filesystem holding CWD
 * May add path selection later, but should not be necessary
 */
static int
list(void) {
	struct hammer2_ioc_pfs lpfs; /* listing pfs */
	int lpfsd; /* listing pfs descriptor */
	char dir[1024];
	
	if ((lpfsd = open(getcwd(&dir,1024), O_RDONLY)) < 0) {
		fprintf(stderr, "Unable to open %s!\n", dir);
		return(-1);
	}

	memset(&lpfs, 0, sizeof(lpfs));
	fprintf(stdout,"HAMMER2 PFSes found in %s\n",dir);
	for(; lpfs.name_key != (hammer2_key_t)-1; lpfs.name_key = lpfs.name_next) {
		if(ioctl(lpfsd, HAMMER2IOC_PFS_GET, &lpfs) < 0) {
			fprintf(stderr, "Unable to get pfs!\n");
			break;
		}
		fprintf(stdout,"%s\n",lpfs.name);
	}
	close(lpfsd);
	return(0);
}

static void __attribute__((noreturn))
usage(void) {
	fprintf(stderr,"%s: Locate and delete PFSes thoughout the filesystem with the same label\n"
			           "\tex: %s [-ly] label1 label2...\n"
								 "\t-h  This help text\n"
								 "\t-l  List PFSes found on the filesystem for CWD\n"
								 "\t-y  Do not ask for confirmation, destroy unconditionally\n",
								 __progname, __progname);
	exit(0);
}

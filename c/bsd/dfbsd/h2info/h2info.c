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

/* necessary system includes */
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/ucred.h>
#include <sys/user.h>

/* bring in the functions to actually access the HAMMER2 filesystems */
#include <vfs/hammer2/hammer2_disk.h>

/* other utilities */
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * This is a tool meant to simply grab and display information on a HAMMER2
 * pfs to the user, possibly as a means of being able to debug what's wrong
 * assuming there is anything wrong. Otherwise, just a fun tool for people like me
 */

extern char *__progname;

int fsinfo(char **filesystems, bool walk);
bool h2check(struct statfs *fs);
int pfsget(char *mountpoint);
void pfsprint(char *mountpoint, hammer2_blockref_t *h2blockref, hammer2_volconf_t *h2volconf, hammer2_inode_meta_t *h2inode);
static void __attribute__((noreturn)) usage(void);

int
main(int argc, char **argv) { 
	int ch;
	bool walk;

	ch = 0;
	walk = false;

	while ((ch = getopt(argc, argv, "hl")) != -1) { 
			switch (ch) { 
				case 'h':
					usage();
				case 'l':
					walk = true;
					break;
			}
	}
	argc -= optind;
	argv += optind;

	if (*argv == NULL && !walk) { 
		usage();
	} else { 
		return(fsinfo(argv, walk));
	}
	/* should not be reachable */
	return(0);
}

/*
 * This function will return the number of filesystems it was able to query
 */
int
fsinfo(char **filesystems, bool walk) { 
	struct statfs *fs;
	long fsbufsize;
	int flags, fscount, rptcount;

	fscount = fsbufsize = rptcount = 0;
	fs = NULL;

	flags = MNT_WAIT;
	/* 
	 * true = walk everything
	 * false = use **filesystems
	 */
	if (walk) { 
		if ((fscount = getfsstat(fs, fsbufsize, flags)) > 0) { 
			fprintf(stderr,"found %d filesystems\n",fscount);
			if ((fs = calloc(sizeof(struct statfs *),fscount)) == NULL) { 
				return(-1);
			}
			fsbufsize = (sizeof(*fs) * fscount);
		}
		if ((fscount = getfsstat(fs, fsbufsize, flags)) <= 0) { 
			fprintf(stderr,"Something went wrong collecting statfs structs!\n");
			return(-1);
		} else { 
			for (flags = 0; flags < fscount; flags++) { 
				if (h2check(&fs[flags])) { 
					if (pfsget(fs[flags].f_mntonname) == -1) { 
						free(fs);
						return(-1);
					} else { 
						rptcount++;
					}
				}
			}
			free(fs);
		}
	} else { 
	}
	return(rptcount);
}

/* 
 * h2check verifies that a given filesystem is actually a HAMMER2 volume
 */
bool
h2check(struct statfs *fs) { 
	if (strncmp(fs->f_fstypename,"hammer2",8) == 0) { 
		fprintf(stderr,"%s: is a HAMMER2 filesystem, continuing\n", fs->f_mntonname);
		return(true);
	} else { 
		fprintf(stderr,"%s: is not a HAMMER2 filesystem, skipping...\n", fs->f_mntfromname);
		return(false);
	}
}

/* 
 * This should get the hammer2 information of a given pfs
 * at the given mountpoint, which can then be passed on to 
 * a printing or stats function
 * Will return a simple status indication of success/fail
 */
int
pfsget(char *mountpoint) {
	return(0);
}

void
pfsprint(char *mountpoint, hammer2_blockref_t *h2blockref, hammer2_volconf_t *h2volconf, hammer2_inode_meta_t *h2inode) { 
	/*
	 * This should probably be called by pfsget(), so 
	 * it needs no logic, simply print the members of the struct 
	 * it is given, the definitions of which would be in hammer2_disk.h
	 */
}

static void
__attribute__((noreturn)) usage(void) { 
	fprintf(stderr,"%s: Simple utility to pull information from a HAMMER2 PFS\n"
			           "%s [-hl] PFS ...\n"
			           "\t-h  This usage information\n"
								 "\t-l  Walk through ALL HAMMER2 filesystems currently mounted (extremely verbose)\n"
								 ,__progname,__progname);
	exit(0);
}

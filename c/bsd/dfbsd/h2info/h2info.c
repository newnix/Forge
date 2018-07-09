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
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/ucred.h>
#include <sys/user.h>

/* bring in the functions to actually access the HAMMER2 filesystems */
#include <vfs/hammer2/hammer2_ioctl.h>

/* other utilities */
#include <err.h>
#include <errno.h>
#include <fcntl.h>
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
int pfsget(struct statfs *mountpoint);
void pfsprint(char *mountpoint, hammer2_blockref_t *h2blockref, hammer2_volconf_t *h2volconf, hammer2_inode_meta_t *h2inode, hammer2_ioc_pfs_t *h2pfs);
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
			if ((fs = calloc(sizeof(struct statfs *),(size_t)fscount)) == NULL) { 
				return(-1);
			}
			fsbufsize = (sizeof(*fs) * fscount);
		}
		if ((fscount = getfsstat(fs, fsbufsize, flags)) <= 0) { 
			err(errno, "getfsstat");
		} else { 
			for (flags = 0; flags < fscount; flags++) { 
				if (h2check(&fs[flags])) { 
					if (pfsget(&fs[flags]) == -1) { 
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
		if ((fs = calloc(sizeof(struct statfs *), 1)) == NULL) { 
			err(errno, "calloc");
		}

		for (; *filesystems != NULL; filesystems++) {
			if (statfs(*filesystems, fs) == -1) { 
				return(-1);
			} else { 
				if (h2check(fs)) { 
					if (pfsget(fs) == -1) { 
						return(-1);
					} else { 
						rptcount++;
					}
				}
			}
		}
		free(fs);
	}
	return(rptcount);
}

/* 
 * h2check verifies that a given filesystem is actually a HAMMER2 volume
 */
bool
h2check(struct statfs *fs) { 
	if (strncmp(fs->f_fstypename,"hammer2",8) == 0) { 
		return(true);
	} else { 
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
pfsget(struct statfs *mountpoint) {
	hammer2_ioc_inode_t h2inode;
	hammer2_ioc_pfs_t h2pfs;
	int fd, fd1;

	fd = fd1 = 0;

	if ((fd = open(mountpoint->f_mntonname, O_RDONLY)) <= 0) {
		err(errno, "open(%s)", mountpoint->f_mntonname);
	}
	if ((fd1 = open(mountpoint->f_mntfromname, O_RDONLY)) <= 0) { 
		err(errno, "open(%s)", mountpoint->f_mntonname);
	}


	if (ioctl(fd, HAMMER2IOC_INODE_GET, &h2inode) != -1) { 
			/* currently unsure what the difference between lookup and get is o the pfs ioctls */
			//if (ioctl(fd1, HAMMER2IOC_PFS_LOOKUP, &h2pfs) != -1) { 
				pfsprint(mountpoint->f_mntonname, &h2inode.ip_data.u.blockset.blockref[0], 
						NULL, &h2inode.ip_data.meta, &h2pfs);
		//} else { 
		//	close(fd);
		//	close(fd1);
		//	err(errno, "HAMMER2IOC_PFS_LOOKUP %s", mountpoint->f_mntonname);
		//}
	} else { 
		close(fd);
		close(fd1);
		err(errno,"HAMMER2IOC_INODE_GET %s", mountpoint->f_mntonname);
	}
	
	memset(&h2inode, 0, sizeof(h2inode));
	memset(&h2pfs, 0, sizeof(h2pfs));
	close(fd);
	close(fd1);
	return(0);
}

void
pfsprint(char *mountpoint, hammer2_blockref_t *h2br, hammer2_volconf_t *h2vc, hammer2_inode_meta_t *h2i, hammer2_ioc_pfs_t *h2pfs) { 
	/*
	 * This should probably be called by pfsget(), so 
	 * it needs no logic, simply print the members of the struct 
	 * it is given, the definitions of which would be in hammer2_disk.h
	 */
	fprintf(stdout,"HAMMER2 filesystem information for %s:\n"
	               "--------------------------------------------------\n"
	               "type: %hhu \tmethods: %u\tcopyid: %u\tkeybits: %u\n"
	               "vradix: %u\tflags: %u\tleaf_count: %u\tkey: %lu\n"
	               "mirror_tid: %lu\tmodify_tid: %lu\tdata_off: %lu\n"
	               "update_tid: %lu\n",mountpoint,
	               h2br->type, h2br->methods, h2br->copyid, h2br->keybits,
	               h2br->vradix, h2br->flags, h2br->leaf_count, h2br->key,
	               h2br->mirror_tid, h2br->modify_tid, h2br->data_off, h2br->update_tid);

	/* fprintf(stdout,"copyid: %hhu\tinprog: %hhu\tchain_to: %hhu\tchain_from: %hhu\n"
	                  "flags: %u\terror: %hhu\tpriority: %hhu\tremote_pfs_type: %hhu\n"
	                  "pfs_clid: %s\tlabel: %s\tpath: %s\n",
	                  h2vc->copyid, h2vc->inprog, h2vc->chain_to, h2vc->chain_from,
	                  h2vc->flags, h2vc->error, h2vc->priority, h2vc->remote_pfs_type,
	                  "NOTIMP", h2vc->label, h2vc->path);
	*/

	fprintf(stdout,"version: %u\tpfs_subtype: %hhu\tuflags: %u\trmajor: %u\n"
	               /* 
	                * Timestamps are generated with getmicrotime(9), which 
	                * populates a timeval struct, which then is used in the following equation:
	                * timestamp = (unsigned long)tv.tv_sec * 1000000 + tv.tv_usec
	                * so a simple divide by 1M should provide the value as seconds in an accurate enough
	                * representation of the actual timestamp.
	                */
	               "rminor: %u\tctime: %lu\tmtime: %lu\tatime: %lu\tbtime: %lu\n"
	               "uid: NOTIMP\tgid: NOTIMP\ttype: %hhu\top_flags: %hhu\n"
	               "cap_flags: %u\tmode: %u\tinum: %lu\tsize: %lu\n"
	               "nlinks: %lu\tiparent: %lu\tname_key: %lu\tname_len: %u\n"
	               "ncopies: %hhu\tcomp_algo: %hhu\ttarget_type: %hhu\tcheck_algo: %hhu\n"
	               "pfs_nmasters: %hhu\tpfs_type: %hhu\tpfs_inum: %lu\tpfs_clid: NOTIMP\tpfs_fsid: NOTIMP\n"
	               "data_quota: %lu\tunusedB8: %lu\tinode_quota: %lu\tunusedC8: %lu\n"
	               "pfs_lsnap_tid: %lu\n\n",
	               h2i->version, h2i->pfs_subtype, h2i->uflags, h2i->rmajor, h2i->rminor, h2i->ctime,
	               h2i->mtime, h2i->atime, h2i->btime, h2i->type, h2i->op_flags, h2i->cap_flags,
	               h2i->mode, h2i->inum, h2i->size, h2i->nlinks, h2i->iparent, h2i->name_key, 
	               h2i->name_len, h2i->ncopies, h2i->comp_algo, h2i->target_type, h2i->check_algo,
	               h2i->pfs_nmasters, h2i->pfs_type, h2i->pfs_inum, h2i->data_quota, h2i->unusedB8,
								 h2i->inode_quota, h2i->unusedC8, h2i->pfs_lsnap_tid);

	fprintf(stdout,"pfs_type: %hhu\tpfs_subtype: %hhu\tpfs_flags: %u\n"
	               "pfs name: %s\n",
	               h2pfs->pfs_type, h2pfs->pfs_subtype, h2pfs->pfs_flags, h2pfs->name);
}

static void
__attribute__((noreturn)) usage(void) { 
	fprintf(stderr,"%s: Simple utility to pull information from a HAMMER2 PFS\n"
	               "%s [-hl] PFS ...\n"
	               "\t-h  This usage information\n"
	               "\t-l  Walk through ALL HAMMER2 filesystems currently mounted (extremely verbose)\n"
	               "\tNote: You may need privilege escalation for this tool to work properly!\n"
	               ,__progname,__progname);
	exit(0);
}

#ifndef __DFBEADM__
#define __DFBEADM__

#define BESEP '-'

/* necessary inclusions for filesystem data */
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/ucred.h>

extern char *__progname;

/*
 * activate a given boot environment
 */
static int
activate(char *label) { 
	return(0);
}

/* 
 * create a boot environment
 */
static int
create(char *label) { 
	/*
	 * I'm not sure that there's a library way to handle this yet, but
	 * using hammer2(8) to create snapshots is effectively the same as creating a
	 * new PFS, but it's created with the type "snapshot". So we'll need to use 
	 * a naming convention like mountpoint-label. Current scheme would be:
	 * /usr/local/bin -> usr.local.bin-20180601, so it's distinct from other 
	 * snapshots of the same PFS, without potentially stomping on reserved characters
	 */
	char befs[MNAMELEN];
	long size;
	int fscount, i;
	struct statfs *filesystems;
	/* first we need to get a list of currently mounted HAMMER2 filesystems */
	fscount = i = 0;
	size = 0;
	filesystems = NULL;

	if ((fscount = getfsstat(filesystems, size, MNT_WAIT)) > 0) {
		if ((filesystems = calloc(sizeof(struct statfs *), fscount)) == NULL) {
			return(-1);
		}
		size = (sizeof(*filesystems) * fscount);
	}

	if ((fscount = getfsstat(filesystems, size, MNT_WAIT)) > 0) {
		for (; i < fscount; i++) {
			/* 
			 * On my desktop HAMMER2 was f_type 9, but on my laptop it's 5.
			 * will need to look into a more reliable way to determine if I'm 
			 * working with a HAMMER2 pfs
			 */
			if (filesystems[i].f_type == 5) {
				snprintf(befs, MNAMELEN, "%s%c%s", filesystems[i].f_mntfromname, BESEP, label);
				fprintf(stderr,"befs[%d/%ld]: %s\n", i, fscount, befs);
				memset(befs, 0, MNAMELEN);
			}
		}
	}

	return(0);
}

/*
 * deactivate the given boot environment
 */
static int
deactivate(char *label) { 
	return(0);
}

/*
 * list the available boot environments
 */
static int
list(void) { 
	/* should return the number of environments found, -1 if error */
	return(0);
}

/*
 * delete a given boot environment
 */
static int
rmenv(char *label) { 
	return(0);
}

/*
 * delete the given snapshot
 */
static int
rmsnap(char *pfs) { 
	return(0);
}

/* 
 * create a pfs snapshot
 */
static int
snapfs(char *pfs) { 
	return(0);
}

/*
 * tell the user how this program works
 */
static void __attribute__((noreturn))
usage(void) { 
	fprintf(stderr,"%s: Utility to create HAMMER2 boot environments.\n",__progname);
	fprintf(stderr,"Usage:\n -a Activate the given boot environment\n -d Deactivate the given boot environment"
	               "\n -h This message\n -l List boot environments\n"
								 " -r Delete the given snapshot\n -s Create a snapshot with the given label"
								 "\n -R Delete the given boot environment\n");
	exit(0);
}
#endif

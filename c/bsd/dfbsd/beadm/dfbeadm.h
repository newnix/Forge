#ifndef DFBEADM
#define DFBEADM

#define PFSDELIM '@'
#define BESEP '-'
#define TMAX 18

/* necessary inclusions for vfs layer data */
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/ucred.h>

/* HAMMER2 specific needs */
#include <vfs/hammer2/hammer2_ioctl.h>

/* this struct should be used for easier passing of necessary information */
typedef struct snaptarget {
	char current[MNAMELEN]; /* current pfs.name value */
	char newfs[MNAMELEN]; /* desired pfs.name value */
	char device[MNAMELEN]; /* where this pfs is physically */
	char mountpoint[MNAMELEN]; /* where it's mounted */
} snapt;

static bool ish2(char *mountpoint);
static void trunc(char *longstring);
static int snapfs(snapt *snapfs);
static void mktargets(snapt *targets, struct statfs *target, int fscount, char *label);

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
	snapt *snaptargets;
	/* first we need to get a list of currently mounted HAMMER2 filesystems */
	fscount = i = 0;
	size = 0;
	filesystems = NULL;
	snaptargets = NULL;

	if (strlen(label) >= MNAMELEN) { 
		fprintf(stderr,"Cannot fit all of %s into boot a environment label,",label);
		trunc(label);
		fprintf(stderr," truncated to %s\n",label);
	}

	if ((fscount = getfsstat(filesystems, size, MNT_WAIT)) > 0) {
		if ((filesystems = calloc(sizeof(struct statfs *), fscount)) == NULL) {
			return(-1);
		}
		size = (sizeof(*filesystems) * fscount);
	}

	if ((fscount = getfsstat(filesystems, size, MNT_WAIT)) > 0) {
		if ((snaptargets = calloc(sizeof(snapt *), fscount)) == NULL) { 
			free(filesystems);
			err(errno, "calloc");
		}
		for (; i < fscount; i++) {
			if (ish2(filesystems[i].f_mntonname)) {
				/*
				 * The 'befs' variable should be what's written to /etc/fstab for the device
				 * name of a given mountpoint, the 'label' variable should get added onto a 
				 * string that alreadly contains the existing PFS name 
				 * (minus the old snapshot label, should it exist)
				 */
				snprintf(befs, MNAMELEN, "%s%c%s", filesystems[i].f_mntfromname, BESEP, label);
				/* 
				 * There will need to be some extra work in constructing the new PFS
				 * name, mostly in ensuring the function to do so accurately detects the 
				 * beginning of the existing boot environment, removes those characters,
				 * and writes the new boot environment name to the ephemeral pfs struct 
				 * before taking the snapshot
				 */
				fprintf(stderr,"befs[%d/%d]: %s\n", i, fscount, befs);
				memset(befs, 0, MNAMELEN);
			}
		}
		mktargets(snaptargets, filesystems, fscount, label);
	}

	free(filesystems);
	free(snaptargets);
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
 * Determine if the given mountpoint is a HAMMER2 filesystem 
 */
static bool
ish2(char *mountpoint) {
	int mp;
	hammer2_ioc_inode_t h2ino;

	mp = 0;
	/* 
	 * additional possible utility is the version info
	 * HAMMER2IOC_VERSION_GET, that wouuld return a 
	 * hammer2_ioc_version_t version.version integer
	 * if successful
	 */
	if ((mp = open(mountpoint, O_RDONLY)) == 0) {
		return(false);
	}
	if (ioctl(mp, HAMMER2IOC_INODE_GET, &h2ino) < 0) {
		close(mp);
		return(false);
	} else {
		close(mp);
		return(true);
	}
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
 * basically create a node in a doubly linked list
 */
static void
mktargets(snapt *targets, struct statfs *target, int fscount, char *label) {
	int i, j, k;
	bool pfs;

	pfs = false;

	/* fill in the structs */
	for(k = 0; k < fscount; k++) { 
		if (ish2(target[k].f_mntonname)) { 
			strlcpy(targets[k].mountpoint, target[k].f_mntonname, MNAMELEN);
			strlcpy(targets[k].newfs, label, MNAMELEN);
			/* 
			 * For reliability, at least with HAMMER2, we should instead grab the 
			 * location of PFSDELIM. Which can then allow two separate loops to be 
			 * run, potentially concurrently, to fill out the two remaining fields
			 * targets[k].current and targets[k].device
			 */
			for (i = j = 0; target[k].f_mntfromname[i] != 0; i++) {
				if (target[k].f_mntfromname[i] == PFSDELIM) { 
					pfs = true; 
					i++; 
					targets[k].device[j] = 0;
					j ^= j; 
				}

				if (pfs) {
					targets[k].current[j] = target[k].f_mntfromname[i];
					j++;
				} else {
					targets[k].device[j] = target[k].f_mntfromname[i];
					j++;
				}
			}
			targets[k].newfs[j] = 0;
			fprintf(stderr,"targets[%d]:\n---------------\n"
										 "current: %s\nnewfs: %s\ndevice: %s\nmountpoint: %s\n"
										 "---------------\n",
										 k, targets[k].current, targets[k].newfs, targets[k].device, targets[k].mountpoint);
		}
	}
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
 * This should ideall be a filesystem agnostic function
 * to create a snapshot with the given label
 */
static int
snapfs(snapt *fstarget) { 
	/* 
	 * This likely uses HAMMER2IOC_PFS_SNAPSHOT to create hammer2 snapshots, will need to reference
	 * the hammer2 utility implementation.
	 * TODO: Turn this function into an abstraction for any CoW filesystem, selected at compile-time
	 * then if I'm able, possibly even available at runtime should multiple CoW filesystems be available
	 * though this could be expanded to any filesystem with the same functionality of snapshots. Possibly 
	 * including both HAMMER and UFS in later versions
	 */
	hammer2_ioc_pfs_t pfs;
	int fd, e;

	e = fd = 0;
	memset(&pfs, 0, sizeof(pfs));

	if ((fd = open(fstarget->mountpoint, O_RDONLY)) <= 0) {
		fprintf(stderr, "Can't open %s!\n%s\n", fstarget->mountpoint, strerror(errno));
	}

	snprintf(pfs.name, sizeof(pfs.name), "%s%c%s", fstarget->current, BESEP, fstarget->newfs);
	fprintf(stderr, "%s\n", pfs.name);
	/* We use the following ioctl() to actually create a snapshot */
	//if (ioctl(fd, HAMMER2IOC_PFS_SNAPSHOT, &pfs) != -1) {
	//	e = 0;
	//	close(fd);
	//} else {
	//	fprintf(stderr, "H2 Snap failed!\n%s\n",strerror(errno));
	//	close(fd);
	//}
	close(fd);
	return(e);
}

/*
 * Cut down a string to fit in the boot environment limitations
 */
static void
trunc(char *longstring) { 
	snprintf(longstring, MNAMELEN, "%s", longstring);
}

/*
 * tell the user how this program works
 */
static void __attribute__((noreturn))
usage(void) { 
	fprintf(stderr,"%s: Utility to create HAMMER2 boot environments.\n",__progname);
	fprintf(stderr,"Usage:\n"
	               "  -a  Activate the given boot environment\n"
	               "  -c  Create a new boot environment with the given label\n"
	               "  -d  Destroy the given boot environment\n"
	               "  -h  This help text\n"
	               "  -l  List existing boot environments\n"
	               "  -r  Remove the given boot environment\n");
	exit(0);
}
#endif

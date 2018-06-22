#ifndef DFBEADM
#define DFBEADM

#define BESEP '-'
#define TMAX 18

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
	char befs[MNAMELEN], timestamp[TMAX];
	long size;
	int fscount, i;
	struct statfs *filesystems;
	time_t tim;
	/* first we need to get a list of currently mounted HAMMER2 filesystems */
	fscount = i = 0;
	size = 0;
	filesystems = NULL;

	if (strlen(label) >= MNAMELEN) { 
		trunc(label);
		fprintf(stderr,"Cannot fit all of %s into boot environment, truncating at %s\n",label,trunc(label));
	}

	if ((fscount = getfsstat(filesystems, size, MNT_WAIT)) > 0) {
		if ((filesystems = calloc(sizeof(struct statfs *), fscount)) == NULL) {
			return(-1);
		}

		/*
		 * for the time being, I'm only going to be concerned with UTC/C time 
		 * additionally, the timestamp in the name is unlikely to be necessary,
		 * as HAMMER2 most likely will have timestamps available in the metadata
		 */
		tim = time(NULL);
		if (strftime(timestamp, TMAX, "%Y%m%d%H%MT%Z", localtime(&tim)) == 0) {
			free(filesystems);
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
			 * This could be a strncmp() call, but that can't be the most efficient 
			 * means of doing this. 
			 */
			snprintf(befs, MNAMELEN, "%s%c%s%c%s", filesystems[i].f_mntfromname, BESEP, label, BESEP, timestamp);
			fprintf(stderr,"befs[%d/%d]: %s\n", i, fscount, befs);
			memset(befs, 0, MNAMELEN);
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
 * This should ideall be a filesystem agnostic function
 * to create a snapshot with the given label
 */
static int
snapfs(char *fstarget, char *label) { 
	return(0);
}

/*
 * Cut down a string to fit in the boot environment limitations
 */
static void
trunc(char *longstring) { 
	uint64_t strlength, strdiff;

	strdiff = strlength = 0;

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

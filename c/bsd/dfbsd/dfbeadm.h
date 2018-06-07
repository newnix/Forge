#ifndef __DFBEADM__
#define __DFBEADM__
/*
 * activate a given boot environment
 */
static int
activate(char *label) { 
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
 * create a boot environment
 */
static int
snap(char *label) { 
	/*
	 * I'm not sure that there's a library way to handle this yet, but
	 * using hammer2(8) to create snapshots is effectively the same as creating a
	 * new PFS, but it's created with the type "snapshot". So we'll need to use 
	 * a naming convention like mountpoint-label. Current scheme would be:
	 * /usr/local/bin -> usr.local.bin-20180601, so it's distinct from other 
	 * snapshots of the same PFS, without potentially stomping on reserved characters
	 */
	/* what follows is mostly conceptual code, not meant to be functional at the moment and subject to change */
	for (; *pfs != NULL; *pfs++) {
		strlcpy(snampname,pfs,FSMAX);
		strlcat(snapname,SNAPSEP,1);
		strlcat(snapname,label,FSMAX);
	}
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
	fprintf(stderr,"dfbeadm: Utility to create HAMMER2 boot environments.\n");
	exit(0);
}
#endif

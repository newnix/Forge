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

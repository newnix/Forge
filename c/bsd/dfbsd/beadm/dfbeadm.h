#ifndef DFBEADM
#define DFBEADM

#define PFSDELIM '@'
#define BESEP ':'
#define TMAX 18

/* necessary inclusions for vfs layer data */
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/ucred.h>

/* for fstab manipulation/verification */
#include <fstab.h>

/* HAMMER2 specific needs */
#include <vfs/hammer2/hammer2_ioctl.h>

/* borderline useless "debug" printout */
#define dbg fprintf(stderr, "Something went wrong in %s: %d!\n", __FILE__, __LINE__);

/* struct to hold the relevant data to rebuild the fstab */
struct bootenv_data { 
	struct fstab fstab; /* this should be pretty obvious, but this is each PFS's description in the fstab */
	char curlabel[NAME_MAX]; /* this may actually not be necessary, bubt it's the current label of the PFS */
	struct hammer2_ioc_pfs snapshot; /* this is the PFS we'll be creating a snapshot with */
	int label_start; /* this is the offset of the fs_spec string where we find the @ sign */
	bool snap;
};

typedef struct bootenv_data bedata;
static int create(char *label);
static bool ish2(char *mountpoint);
static void trunc(char *longstring);
static void mktargets(bedata *target, int fscount, char *label);
static int relabel(bedata *fs, char *label);
static int snapfs(bedata *snapfs, int fscount, char *label);

extern char *__progname;


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

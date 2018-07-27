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

#include <sys/types.h>
#include <sys/mman.h>

#include <fstab.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 
 * This tool simply creates and tests the validity of an ephemeral fstab
 */
#define FSTAB_MAX 128
#define BESEP ':'
extern char **environ;
extern char *__progname;

static size_t countfs(void);
static size_t efstab(const char *fstab, const char *label, size_t fscount);
static unsigned short ish2(const char *vfstype);
static void printfs(const char *fstab);
static void __attribute__((noreturn)) usage(void);

int
main(int ac, char **av) {
	char fstab[FSTAB_MAX], label[FSTAB_MAX];
	int op;

	op = 0;
	
	/* set the default ephemeral fstab location */
	if (snprintf(fstab, FSTAB_MAX, "/tmp/.fstab_%s.%d",getenv("LOGNAME"),getpid()) <= 0) { 
		fprintf(stderr,"Something has gone horribly wrong, bailing out...\n");
		exit(3);
	}

	while ((op = getopt(ac, av, "hf:l:")) != -1) {
		switch (op) {
			case 'h':
				usage();
			case 'f':
				snprintf(fstab, FSTAB_MAX, "PATH_FSTAB=%s", optarg);
				break;
			case 'l':
				strlcpy(label, optarg, FSTAB_MAX);
				break;
			default:
				usage();
		}
	}

	putenv(fstab);
	/* 
	 * invoke efstab() with the live fstab, so we can read valid data out of it
	 * and write the modifications to a separate struct dynamically built,
	 * which then is written to the ephemeral file before verification
	 */
	if (efstab(fstab, label, countfs()) > 0) {
		printfs(fstab);
		fprintf(stdout, "Cleaning up...\nRemoving %s from filesystem...\n",fstab);
		return(unlink(fstab));
	} else { 
		fprintf(stderr, "Something went wrong! No filesystems written to %s!\n", fstab);
		fprintf(stderr, "Deleting empty file at %s...\n", fstab);
		unlink(fstab);
		return(2);
	}
}

/* get the number of fstab structs we need to build */
static size_t
countfs(void) {
	size_t i;
	struct fstab *fs;

	/* ensure we use the system fstab */
	setfstab("/etc/fstab");

	for (i = 0; (fs = getfsent()) != NULL; i++) {
		/* just spin it up */
	}
	endfsent();
	return(i);
}

/* This part generates the file */
static size_t 
efstab(const char *fstab, const char *label, size_t fscount) {
	size_t written;
	struct fstab *current, *efs;
	FILE *fp;
	current = NULL;
	efs = NULL;
	fp = NULL;
	written = 0; /* default to erroring out */

	fprintf(stderr, "Attempting to get a buffer of %lu * %lu bytes...\n", sizeof(struct fstab), fscount);
	/* 
	 * this actually isn't necessary for the purpose of generating and reading back an
	 * fstab file, but since this is meant to create a modified copy, we want to be able to 
	 * dynamically allocate enough space for the modified version to be held in RAM before
	 * writing to the temp file.
	 * Forgot to allocate space for the actual char * members. Since the struct is built like so:
	 * struct fstab { 
	 *	char *fs_spec;
	 *	char *fs_file;
	 *	char *fs_vfstype;
	 *	char *fs_mntops;
	 *	char *fs_type;
	 *	int fs_freq;
	 *	int fs_passno;
	 * };
	 */
	if ((efs = calloc(fscount, sizeof(struct fstab))) == NULL) { 
		fprintf(stderr, "Cannot allocate memory for efstab()\n");
		return(written);
	} else {
		for (written = 0; written < fscount; written++) {
			/* now try allocating space for all the members of the struct */
			if ((efs[written].fs_spec = calloc(1, FSTAB_MAX)) == NULL) {
				free(efs);
				return(0);
			}
			if ((efs[written].fs_file = calloc(1, FSTAB_MAX)) == NULL) {
				free(efs);
				return(0);
			}
			if ((efs[written].fs_vfstype = calloc(1, FSTAB_MAX)) == NULL) {
				free(efs);
				return(0);
			}
			if ((efs[written].fs_mntops = calloc(1, FSTAB_MAX)) == NULL) {
				free(efs);
				return(0);
			}
			if ((efs[written].fs_type = calloc(1, FSTAB_MAX)) == NULL) {
				free(efs);
				return(0);
			}
		}
	}

	/* open the system file to copy out */
	setfstab("/etc/fstab");
	fprintf(stdout,"System fstab info: (%s, %lu filesystems)\n-----------------------------------\n",getfstab(), fscount);
	printfs(getfstab());
	endfsent();
	setfstab("/etc/fstab");
	/* actually need to open the ephemeral file */
	for (written = 0; written < fscount; written++) {
		current = getfsent();
		if (ish2(current->fs_vfstype)) {
			/* tediously copy everything into place */
			snprintf(efs[written].fs_spec, FSTAB_MAX, "%s%c%s", current->fs_spec, BESEP, label);
			strlcpy(efs[written].fs_file, current->fs_file, FSTAB_MAX);
			strlcpy(efs[written].fs_vfstype, current->fs_vfstype, FSTAB_MAX);
			strlcpy(efs[written].fs_mntops, current->fs_mntops, FSTAB_MAX);
			strlcpy(efs[written].fs_type, current->fs_type, FSTAB_MAX);
			efs[written].fs_freq = current->fs_freq;
			efs[written].fs_passno = current->fs_passno;
		} else {
			strlcpy(efs[written].fs_spec, current->fs_spec, FSTAB_MAX);
			strlcpy(efs[written].fs_file, current->fs_file, FSTAB_MAX);
			strlcpy(efs[written].fs_vfstype, current->fs_vfstype, FSTAB_MAX);
			strlcpy(efs[written].fs_mntops, current->fs_mntops, FSTAB_MAX);
			strlcpy(efs[written].fs_type, current->fs_type, FSTAB_MAX);
			efs[written].fs_freq = current->fs_freq;
			efs[written].fs_passno = current->fs_passno;
		}
	}
	/* close system file, switch to ephemeral file */
	endfsent();
	setfstab(fstab);

	if ((fp = fopen(fstab, "a")) == NULL) {
		fprintf(stderr, "Could not open %s for writing, bailing out...\n", fstab);
		return(0);
	}

	for (written = 0; written < fscount; written++) { 
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%d\t%d\n",
		            efs[written].fs_spec, efs[written].fs_file, efs[written].fs_vfstype,
								efs[written].fs_mntops, efs[written].fs_type,
								efs[written].fs_freq, efs[written].fs_passno);
	}
	fclose(fp);
	/* ensure we clean up */
	for (written = 0; written < fscount; written++) {
		free(efs[written].fs_spec);
		free(efs[written].fs_file);
		free(efs[written].fs_vfstype);
		free(efs[written].fs_mntops);
		free(efs[written].fs_type);
	}
	free(efs);
	return(written);
}

static unsigned short
ish2(const char *fs) {
	if (fs[0] == 'h') { 
		return(1);
	} else {
		return(0);
	}
}

/* This will verify the file */
static void
printfs(const char *fstab) {
	struct fstab *fsent;

	fsent = NULL;

	setfstab(fstab);

	fprintf(stdout,"\nReading from %s:\n--------------------------------------------------\n",fstab);
	while ((fsent = getfsent()) != NULL) {
		fprintf(stdout,"%s\t%s\t%s\t%s\t%s\t%d\t%d\n",
		               fsent->fs_spec, fsent->fs_file, fsent->fs_vfstype,
									 fsent->fs_mntops, fsent->fs_type, fsent->fs_freq,
									 fsent->fs_passno);
	}
	endfsent();
}

static void __attribute__((noreturn))
usage(void) {
	fprintf(stderr, "%s: Generate and test an ephemeral fstab\n"
	                "  -h This message\n"
									"  -f Name of the ephemeral fstab file (optional)\n"
									"  -l Boot environment label\n",
									__progname);
	exit(0);
}

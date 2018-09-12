#ifndef FSUP_H
#define FSUP_H
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
 * Special activation function, for use by the create() chain of functions
 * since we already have all the information necessary to generate and install
 * the fstab data
 */
static int
autoactivate(bedata *snapfs, int fscount, const char *label) {
	/* should probably have an int in there to ensure proper iteration */
	int i;
	char *efstab;
	FILE *efd;
	
	if ((efstab = calloc((size_t)512, sizeof(char))) == NULL) { 
		fprintf(stderr,"Unable to allocate buffer for *efstab!\n");
		return(-1);
	}

	/* generate the name of the ephemeral fstab file */
	snprintf(efstab, (size_t)512, "/tmp/.fstab.%s_%u", label, getpid());

	if ((efd = fopen(efstab, "a")) == NULL) { 
		fprintf(stderr, "Unable to open %s for writing!\n", efstab);
		free(efstab);
		return(-1);
	}

	for (i = 0; i < fscount; i++) {
		fprintf(efd, "%s\t%s\t%s\t%s\t%d\t%d\n", snapfs->fstab.fs_spec, snapfs->fstab.fs_file, 
				                                         snapfs->fstab.fs_vfstype, snapfs->fstab.fs_mntops,
                                                 snapfs->fstab.fs_freq, snapfs->fstab.fs_passno);
	}

	setfstab(efstab);
	printfs(getfstab());
	/* this may be doable in a more clean manner, but it should work properly */
	fprintf(stdout,"Creating backup fstab...\n");
	/* I'm not sure if this is necessarily correct, but it supposedly guarantees some atomicity in its operation */
	rename("/etc/fstab", "/etc/fstab.bak");
	fprintf(stdout,"Installing new fstab...\n");
	rename(efstab, "/etc/fstab");
	unlink(efstab);
	fclose(efd);
	free(efstab);
	return(0);
}

/*
 * activate a given boot environment
 */
static int
activate(const char *label) { 
	/* 
	 * the *label parameter is only used for the pfs lookups, by default this is called by create()
	 * we'll scan currently mounted filesystems for the given boot environment label, and use that to 
	 * create the ephemeral fstab, which then replaces the current fstab, putting it in fstab.label
	 * assuming there was a label. If no label exists for the existing fstab, we'll simply call it 
	 * fstab.bak
	 */
	char *efstab;
	FILE *efd;

	if ((efstab = calloc((size_t)512, sizeof(char))) == NULL) {
		fprintf(stderr,"Error Allocating Ephemeral fstab\n");
	}

	snprintf(efstab, (size_t)512, "/tmp/.fstab.%d.%s", getpid(), label);
	fprintf(stderr, "Created Ephemeral fstab at %s", efstab);

	if ((efd = fopen(efstab, "a")) == NULL) { 
		err(errno, "%s: %s: ", __progname, efstab);
	}

	fclose(efd);
	free(efstab);
	return(0);
}

/*
 * deactivate the given boot environment
 */
static int
deactivate(const char *label) { 
	/* 
	 * I'm not sure what this function will do in particular as the 
	 * naming convention described above is fstab.label, making it trivial to swap boot environments 
	 * This function likely only needs to be called when destroying a boot environment
	 */
	return(0);
}

/*
 * delete a given boot environment
 */
static int
rmenv(const char *label) { 
	return(0);
}

/*
 * delete the given snapshot
 */
static int
rmsnap(const char *pfs) { 
	return(0);
}

static void
printfs(const char *fstab) { 
	struct fstab *fsent;

	fsent = NULL;
	while ((fsent = getfsent()) != NULL) {
		fprintf(stdout,"%s\t%s\t%s\t%s\t%s\t%d\t%d\n",
		               fsent->fs_spec, fsent->fs_file, fsent->fs_vfstype,
									 fsent->fs_mntops, fsent->fs_type, fsent->fs_freq,
									 fsent->fs_passno);
	}
	endfsent();
}
#endif

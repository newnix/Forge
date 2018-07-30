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

/* only define things once */
#ifndef FSCOLLECT_H
#define FSCOLLECT_H

/* 
 * create a boot environment
 * returns 0 if successful, 1 if error, >=2 if things have gone horribly wrong
 */
static int
create(char *label) { 
	/* since we can't rely on the VFS layer for all of our fstab data, we need to be sure what exists */
	int i, fstabcount, vfscount;
	struct fstab *fsptr;
	struct statfs *vfsptr;
	bedata *befs;
	
	fstabcount = vfscount = 0;
	fsptr = NULL;
	vfsptr = NULL;

	if ((vfscount = getfsstat(vfsptr, 0, MNT_WAIT)) == 0) { 
		fprintf(stderr, "Something's wrong, no filesystems found\n");
	}
	do {
		fstabcount++;
	} while ((fsptr = getfsent()) != NULL);
	/* ensure that if we start reading the system fstab again, we start from the top */
	endfsent();

	/* since there's bound to be a swap partition, decrement fstabcount by one */
	if ((fstabcount - 1) != vfscount) {
		fprintf(stderr, "Filesystem counts differ! May have unintended side-effects!\n"
		                "fstab count: %d\nvfs count: %d\n",fstabcount, vfscount);
	} else {
		fprintf(stdout, "VFS Layer and FSTAB(5) are in agreement, generating list of boot environment targets...\n");
	}

	/* now that we have an idea what we're working with, let's go about cloning this data */
	if ((befs = calloc((size_t) fstabcount, sizeof(bedata))) == NULL) {
		fprintf(stderr,"Could not allocate initial buffer!\n");
		return(2); /* probably OOM */
	}

	/* now allocate space for the members */
	for (i = 0; i < fstabcount; i++) {
		if ((befs[i].fstab.fs_spec = calloc(MNAMELEN, 1)) == NULL) {
			fprintf(stderr, "Could not allocate buffer\n");
			free(befs);
			return(2);
		}
		if ((befs[i].fstab.fs_file = calloc(MNAMELEN, 1)) == NULL) {
			fprintf(stderr, "Could not allocate buffer\n");
			free(befs);
			return(2);
		}
		if ((befs[i].fstab.fs_vfstype = calloc(MNAMELEN, 1)) == NULL) {
			fprintf(stderr, "Could not allocate buffer\n");
			free(befs);
			return(2);
		}
		if ((befs[i].fstab.fs_mntops = calloc(MNAMELEN, 1)) == NULL) {
			fprintf(stderr, "Could not allocate buffer\n");
			free(befs);
			return(2);
		}
		if ((befs[i].fstab.fs_type = calloc(MNAMELEN, 1)) == NULL) {
			fprintf(stderr, "Could not allocate buffer\n");
			free(befs);
			return(2);
		}
	}

	/* now pass the buffers to the next step */
	mktargets(befs, fstabcount, label);

	/* ensure we clean up after ourselves */
	for (i ^= i; i < fstabcount; i++) { 
		free(befs[i].fstab.fs_spec);
		free(befs[i].fstab.fs_file);
		free(befs[i].fstab.fs_vfstype);
		free(befs[i].fstab.fs_mntops);
		free(befs[i].fstab.fs_type);
	}
	free(fefs);
	return(0);
}

/* 
 * Creates a buffer of targets to be handed off to snapfs()
 * This function should be called directly from create(), and provided
 * with a buffer of currently existing filesystems
 */
static void
mktargets(bedata *target, int fscount, char *label) {
}
#endif

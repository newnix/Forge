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
	char befs[NAME_MAX];
	long size;
	int fscount, i;
	struct statfs *filesystems;
	/* first we need to get a list of currently mounted HAMMER2 filesystems */
	fscount = i = 0;
	size = 0;
	filesystems = NULL;

	/* ensure befs is 0'd */
	memset(&befs, 0, sizeof(befs));
	if (strlen(label) >= NAME_MAX) { 
		fprintf(stderr,"Cannot fit all of %s into boot a environment label,",label);
		trunc(label);
		fprintf(stderr," truncated to %s\n",label);
	}

	if ((fscount = getfsstat(filesystems, size, MNT_WAIT)) > 0) {
		size = (sizeof(*filesystems) * fscount);
	}

	if ((filesystems = calloc((size_t)fscount, sizeof(struct statfs))) == NULL) { 
		err(errno, "calloc");
	}

	if ((fscount = getfsstat(filesystems, size, MNT_WAIT)) > 0) {
		for (i = 0; i < fscount; i++) {
			/*
			 * The 'befs' variable should be what's written to /etc/fstab for the device
			 * name of a given mountpoint, the 'label' variable should get added onto a 
			 * string that alreadly contains the existing PFS name 
			 * (minus the old snapshot label, should it exist)
			 */
			snprintf(befs, NAME_MAX, "%s%c%s", filesystems[i].f_mntfromname, BESEP, label);
			/* 
			 * There will need to be some extra work in constructing the new PFS
			 * name, mostly in ensuring the function to do so accurately detects the 
			 * beginning of the existing boot environment, removes those characters,
			 * and writes the new boot environment name to the ephemeral pfs struct 
			 * before taking the snapshot
			 */
			fprintf(stderr,"befs[%02d/%02d]: %s\n", i, fscount, befs);
			memset(befs, 0, NAME_MAX);
		}
		mktargets(filesystems, fscount, label);
	}

	free(filesystems);
	return(0);
}

/* 
 * basically create a node in a doubly linked list
 */
static void
mktargets(struct statfs *target, int fscount, char *label) {
	int i;
	bedata *targets;
	targets = NULL;
	/* TODO: get buffer managed by calloc() and appended via realloc() */
	/* 
	 * this should only take the given mountpoints through the statfs buffer
	 * and build a buffer of snapfs targets (or even just build the new pfs structs directly)
	 * that then get passed off to the snapfs() function, but we would ideally 
	 * update fscount and pass that as well so we aren't doing a test for NULL that could
	 * potentially fail if we get uninitialized code
	 */
	if ((targets = calloc(fscount, sizeof(bedata))) == NULL) {
		err(errno, "calloc");
	} 
	for (i = 0; i < fscount; i++) {
		if ((targets[i].fstab.fs_spec = calloc(1, MNAMELEN)) == NULL) {
			free(targets);
			exit(1);
		}
		if ((targets[i].fstab.fs_spec = calloc(1, MNAMELEN)) == NULL) {
			free(targets);
			exit(1);
		}
		if ((targets[i].fstab.fs_spec = calloc(1, MNAMELEN)) == NULL) {
			free(targets);
			exit(1);
		}
		if ((targets[i].fstab.fs_spec = calloc(1, MNAMELEN)) == NULL) {
			free(targets);
			exit(1);
		}
		if ((targets[i].fstab.fs_spec = calloc(1, MNAMELEN)) == NULL) {
			free(targets);
			exit(1);
		}
	}

	/* now we need to actually fill the structs using the data we have from create() */
	for (i ^= i; i < fscount; i++) {
		if (ish2(target[i].f_fstypename)) {
		} else { 
			strlcpy(targets[i].fstab.fs_spec, target[i].f_mntfromname, MNAMELEN);
			strlcpy(targets[i].fstab.fs_file, target[i].f_mntonname, MNAMELEN);
			strlcpy(targets[i].fstab.fs_vfstype, target[i].f_fstypename, MNAMELEN);
		}
	}

	/* send the targets off to have snapshots created */
	snapfs(targets, fscount, label);

	/* cleanup */
	for (i = 0; i < fscount; i++) { 
		free(targets[i].fstab.fs_spec);
		free(targets[i].fstab.fs_file);
		free(targets[i].fstab.fs_vfstype);
		free(targets[i].fstab.fs_mntops);
		free(targets[i].fstab.fs_type);
	}
	free(targets);
}


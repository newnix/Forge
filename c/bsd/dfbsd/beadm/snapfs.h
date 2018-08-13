#ifndef SNAPFS_H
#define SNAPFS_H
/* 
 * This should ideall be a filesystem agnostic function
 * to create a snapshot with the given label
 * Honestly, with the current bedata definitions, fscount and label may not be necessary parameters
 */
static int
snapfs(bedata *fstarget, int fscount, char *label) { 
	/* 
	 * This likely uses HAMMER2IOC_PFS_SNAPSHOT to create hammer2 snapshots, will need to reference
	 * the hammer2 utility implementation.
	 * TODO: Turn this function into an abstraction for any CoW filesystem, selected at compile-time
	 * then if I'm able, possibly even available at runtime should multiple CoW filesystems be available
	 * though this could be expanded to any filesystem with the same functionality of snapshots. Possibly 
	 * including both HAMMER and UFS in later versions
	 */
	int fd, i;
	char newfs[NAME_MAX];

	i = fd = 0;
	for (i ^= i; i < fscount; i++) {
		if (fstarget[i].snap) {
			if ((fd = open(fstarget[i].fstab.fs_file, O_RDONLY)) <= 0) {
				fprintf(stderr, "Can't open %s!\n%s\n", fstarget[i].fstab.fs_file, strerror(errno));
			}
			fprintf(stderr, "Creating snapshot %s...\nOld label: %s\n", fstarget[i].fstab.fs_spec, fstarget[i].curlabel);

			newfs = xtractLabel(fstarget[i].fstab.fs_spec);
			//snprintf(pfs.name, sizeof(pfs.name), "%s%c%s", fstarget->current, BESEP, fstarget->newfs);
			//fprintf(stderr, "%s\n", pfs.name);
			/* We use the following ioctl() to actually create a snapshot */
			//if (ioctl(fd, HAMMER2IOC_PFS_SNAPSHOT, &pfs) != -1) {
			//	e = 0;
			//	close(fd);
			//} else {
			//	fprintf(stderr, "H2 Snap failed!\n%s\n",strerror(errno));
			//	close(fd);
			//}
			fprintf(stderr, "Closing fd %d for mountpoint %s\n", fd, fstarget[i].fstab.fs_file);
			close(fd);
			memset(newfs, 0, NAME_MAX);
		}
	}
	return(0);
}

static char *
xtractLabel(char *newfs) {
	/* this function just returns the PFS label of the new snapshot */
}
#endif

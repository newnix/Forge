#ifndef SNAPFS_H
#define SNAPFS_H
/* 
 * This should ideall be a filesystem agnostic function
 * to create a snapshot with the given label
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
	int fd, e;

	e = fd = 0;

	//if ((fd = open(fstarget->mountpoint, O_RDONLY)) <= 0) {
	//	fprintf(stderr, "Can't open %s!\n%s\n", fstarget->mountpoint, strerror(errno));
	//}

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
	//close(fd);
	return(0);
}

#endif

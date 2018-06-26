#ifdef FREEBSD

static void
fsprint(struct statfs *fsbuf) {
	fprintf(stdout,"f_version: %u\tf_type: %u\tf_flags: %lu\tf_bsize: %lu\n"
			           "f_iosize: %lu\tf_blocks: %lu\tf_bfree: %lu\tf_bavail: %lu\n"
								 "f_files: %lu\tf_ffree: %ld\tf_syncwrites: %lu\tf_asyncwrites: %lu\n"
								 "f_syncreads: %lu\tf_asyncreads: %lu\tf_namemax: %u\tf_owner: %u\n"
								 "f_fsid: %d %d\nf_fstypename: %s\nf_mntfromname: %s\nf_mntonname: %s\n",
								 fsbuf->f_version, fsbuf->f_type, fsbuf->f_flags, fsbuf->f_bsize, fsbuf->f_iosize, fsbuf->f_blocks, fsbuf->f_bfree,
								 fsbuf->f_bavail, fsbuf->f_files, fsbuf->f_ffree, fsbuf->f_syncwrites, fsbuf->f_asyncwrites,
								 fsbuf->f_syncreads, fsbuf->f_asyncreads, fsbuf->f_namemax, fsbuf->f_owner, fsbuf->f_fsid.val[0],
								 fsbuf->f_fsid.val[1], fsbuf->f_fstypename, fsbuf->f_mntfromname, fsbuf->f_mntonname);
}

static void
vfsprint(struct statvfs *vfsbuf) {
	fprintf(stdout,"statvfs(3) not trusted on this platform!\n");
}	

#elif DRAGONFLY

static void
fsprint(struct statfs *fsbuf) { 
	fprintf(stdout,"f_bsize: %ld\tf_iosize: %ld\tf_blocks: %ld\n"
		           "f_bfree: %ld\tf_bavail: %ld\tf_files: %ld\n"
							 "f_ffree: %ld\tf_fsid: %d %d\tf_owner: %u\n"
							 "f_type: %d\tf_flags: %d\tf_syncwrites: %ld\n"
							 "f_asyncwrites: %ld\tf_fstypename: %s\tf_mntonname: %s\n"
							 "f_syncreads: %ld\tf_asyncreads: %ld\tf_mntfromname: %s\n\n",
							 fsbuf->f_bsize, fsbuf->f_iosize, fsbuf->f_blocks, 
							 fsbuf->f_bfree, fsbuf->f_bavail, fsbuf->f_files, 
							 fsbuf->f_ffree, fsbuf->f_fsid.val[0], fsbuf->f_fsid.val[1], fsbuf->f_owner, 
							 fsbuf->f_type, fsbuf->f_flags, fsbuf->f_syncwrites, 
							 fsbuf->f_asyncwrites, fsbuf->f_fstypename, fsbuf->f_mntonname, 
							 fsbuf->f_syncreads, fsbuf->f_asyncreads, fsbuf->f_mntfromname);
}

static void
vfsprint(struct statvfs *vfsbuf) { 
	fprintf(stdout,"f_bsize: %lu\tf_frsize: %lu\tf_blocks: %lu\n"
		           "f_bfree: %lu\tf_bavail: %lu\tf_files: %lu\n"
							 "f_ffree: %lu\tf_favail: %lu\tf_fsid: %lu\n"
							 "f_flag: %lu\tf_namemax: %lu\tf_owner: %u\n"
							 "f_type: %u\nf_syncreads: %lu\tf_syncwrites: %lu\n"
							 "f_asyncreads: %lu\tf_asyncwrites: %lu\n",
							 vfsbuf->f_bsize, vfsbuf->f_frsize, vfsbuf->f_blocks, vfsbuf->f_bfree, 
							 vfsbuf->f_bavail, vfsbuf->f_files, vfsbuf->f_ffree, vfsbuf->f_favail, 
							 vfsbuf->f_fsid, vfsbuf->f_flag, vfsbuf->f_namemax, vfsbuf->f_owner, 
							 vfsbuf->f_type, vfsbuf->f_syncreads, vfsbuf->f_syncwrites, vfsbuf->f_asyncreads, 
							 vfsbuf->f_asyncwrites);
}

#endif

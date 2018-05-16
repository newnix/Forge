/*
 * Simple test program to see how the dir(3) and stat(2) 
 * calls can work together
 */
#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void printstat(struct stat *ent);

int 
main(int argc, char **argv) {
	DIR *dirp;
	struct dirent *entry;
	struct stat *ent;

	dirp = NULL;
	entry = NULL;
	if ((ent = calloc(1, sizeof(ent))) == NULL) { 
		fprintf(stderr,"Not enough memory for statent!\n");
	}

	for (; *argv != NULL; argv++) { 
		if ((dirp = opendir(*argv)) != NULL) { 
			while ((entry = readdir(dirp)) != NULL) { 
				if (lstat(entry->d_name,ent) == 0) {
					fprintf(stdout,"\n%s:\n",entry->d_name);
					printstat(ent);
				} else {
					fprintf(stderr,"dir: cannot read data for %s!\n",entry->d_name);
				}
			}
		}
	}

	closedir(dirp);
	free(ent);
	return(0);
}

static void
printstat(struct stat *ent) {
	fprintf(stdout,"inode:\t%lu\tlinks:\t%d\n"
								 "device:\t%d\tmode:\t%03o\n"
								 "uid:\t%d\tgid:\t%d\n"
								 "dev type:\t%u\n"
								 "size:\t%lu\tblocks:\t%ld\n"
								 "blksize:\t%u\tflags:\t%u\n"
								 "gen:\t%u\tlspare:\t%d\n"
								 "qspare1:\t%ld\tqspare2:\t%ld\n",
								 ent->st_ino,ent->st_nlink,ent->st_dev,ent->st_mode,
								 ent->st_uid,ent->st_gid,ent->st_rdev,ent->st_size,
								 ent->st_blocks,ent->st_blksize,ent->st_flags,ent->st_gen,
								 ent->st_lspare,ent->st_qspare1,ent->st_qspare2);
}

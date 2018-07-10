/* Copyright (c) 2018, Exile Heavy Industries
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

#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <vfs/hammer2/hammer2_disk.h>
#include <vfs/hammer2/hammer2_ioctl.h>

int pfsget(char *mountpoint);
void pfsprint(hammer2_ioc_pfs_t *pfs);
void __attribute__((noreturn)) usage(void);

extern char *__progname;

int 
main(int ac, char **av) {
	av++;

	if (strncmp(*av, "help", 5) == 0) {
		usage();
	}

	for (; *av != NULL; av++) {
		fprintf(stdout, "Found information for %d PFSes in %s\n", pfsget(*av), *av);
	}
	return(0);
}

int
pfsget(char *mountpoint) {
	hammer2_ioc_pfs_t pfs;
	int fd, pfscount;

	pfscount = 0;

	if ((fd = open(mountpoint, O_RDONLY)) <= 0) {
		fprintf(stderr, "Error opening %s!\n", mountpoint);
	}

	memset(&pfs, 0, sizeof(pfs));
	while ((pfs.name_key = pfs.name_next) != (hammer2_key_t)-1) {
		if (ioctl(fd, HAMMER2IOC_PFS_GET, &pfs) <0) { 
			fprintf(stderr, "Error getting PFS info!\n");
			break;
		} else {
			pfsprint(&pfs);
			pfscount++;
		}
	}
	close(fd);
	return(pfscount);
}

void
pfsprint(hammer2_ioc_pfs_t *pfs) {
	fprintf(stdout, "name_key: %lu\tname_next: %lu\n"
	                "pfs_type: %hhu\tpfs_subtype: %hhu\tpfs_flags: %u\n"
									"name: %s\n", pfs->name_key, pfs->name_next, pfs->pfs_type,
									pfs->pfs_subtype, pfs->pfs_flags, pfs->name);
}


void __attribute__((noreturn))
usage() {
	fprintf(stderr, "%s: Print information for all PFSes found at the given mountpoint(s)\n"
	                "  eg: %s /home /build\n", __progname, __progname);
	exit(0);
}

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <vfs/hammer2/hammer2_ioctl.h>

#define PFSDELIM '@'
#define BESEP '-'

extern char *__progname;

int getpfs(char *mountpoint);
int snapfs(hammer2_ioc_pfs_t *pfs, char *label);
void __attribute__((noreturn)) usage(void);

int 
main(int ac, char **av) { 
	int ch;
	char label[NAME_MAX];

	while ((ch = getopt(ac, av, "l:h")) != -1) {
		switch (ch) {
			case 'l':
				strlcpy(label, optarg, NAME_MAX);
				break;
			case 'h':
				usage();
			default:
				usage();
		}
	}
	ac -= optind;
	av += optind;

	/* now go through and create snapshots */
	for (; *av != NULL; av++) {
		getpfs(*av);
	}

	return(0);
}

/* 
 * take a mountpoint and pass off the corresponding mountpoint 
 * to snapfs(), at either point we can throw an error by returning a
 * nonzero number
 */
int
getpfs (char *mountpoint) {
	return(0);
}

/* 
 * take the pfs pulled up via getpfs() and create a snapshot with the 
 * label of *label
 */
int
snapfs (hammer2_ioc_pfs_t *pfs, char *label) {
	return(0);
}

void __attribute__((noreturn))
usage (void) {
	fprintf(stderr, "%s: Create a snapshot of a HAMMER2 PFS\n"
	                " -h This help text\n -l Define the snapshot label\n"
									"    e.g.: %s -l testing /home\n\n", __progname, __progname);
	exit(0);
}

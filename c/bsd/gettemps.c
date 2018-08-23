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
 */

#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/gmon.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>

#define MAXSTR 1024

char *gettemps(int ncpu);

int
main(int ac, char **av) { 
	int  mib[6] = { 0, 0, 0, 0, 0 };
	size_t miblen, mib2len;
	int mib2[3] = { CTL_HW, HW_NCPU, 0 };
	int ncpu;
	mib2len = sizeof(ncpu);
	miblen = sizeof(mib);
	char *test;

	for (++av; *av != NULL; av++) { 
		if (sysctlnametomib(*av, mib, &miblen) == -1) { 
			fprintf(stderr, "ERR: %s: %s\n", *av, strerror(errno));
			break;
		}
		fprintf(stdout,"%s = %d.%d.%d.%d.%d.%d\n", *av, mib[0], mib[1], mib[2], mib[3], mib[4], mib[5]);
		mib[0] ^= mib[0]; mib[1] ^= mib[1]; mib[2] ^= mib[2];
		mib[3] ^= mib[3]; mib[4] ^= mib[4]; mib[5] ^= mib[5];
	}

/* 
 * this part actually tries to get the cpu temp info
 */

	if (sysctl(mib2, mib2len, &ncpu, &mib2len, NULL, 0) < 0) {
		fprintf(stderr,"ERR: %s: sysctl(hw.ncpu) : %d\n", strerror(errno), ncpu);
	}

	test = gettemps(ncpu);
	fprintf(stdout, "%d cores found, temp:%s\n", ncpu, test);
	return(0);
}

char *
gettemps(int ncpu) { 
	int cpu;
	int thermalmib[6] = { 6, 302, 275, 259, 256, 0};
	size_t mibsize, tempsize;
	static char temps[MAXSTR];
	char buf[32];
	double tz0;

	cpu = 0; 
	mibsize = sizeof(thermalmib);
	tempsize = sizeof(tz0);

	if (sysctl(thermalmib, mibsize, &tz0, &mibsize, NULL, 0) < 0) { 
		fprintf(stderr, "ERR: sysctl(3): %s\n", strerror(errno));
		return(NULL);
	}
	return(temps);
}

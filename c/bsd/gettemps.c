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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>

#define MAXSTR 1024

char *gettemps(int ncpu);

int
main(int ac, char **av) { 
	int  mib[6] = { 0, 0, 0, 0, 0, 0 };
	size_t miblen, ncpulen;
	int ncpumib[4] = { 6, 3 };
	int ncpu;
	ncpulen = 4;
	miblen = 6;
	char *test;

	fprintf(stdout, "ncpulen: %lu\nmiblen: %lu\n", ncpulen, miblen);
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

	if (sysctl(ncpumib, ncpulen, &ncpu, &ncpulen, NULL, 0) < 0) {
		fprintf(stderr,"ERR: %s: sysctl(hw.ncpu) : %d\n", strerror(errno), ncpu);
		fprintf(stderr, "sysctl(%d.%d, %lu, %p, %p, NULL, 0) failed, trying sysctlbyname()\n",
				            ncpumib[0], ncpumib[1], ncpulen, &ncpu, &ncpulen);
		if (sysctlbyname("hw.ncpu", &ncpu, &ncpulen, NULL, 0) < 0) {
			fprintf(stderr, "ERR: %s: got %d\n", strerror(errno), ncpu);
		}
	}

	test = gettemps(ncpu);
	fprintf(stdout, "%d cores found, temp:%s\n", ncpu, test);
	return(0);
}

char *
gettemps(int ncpu) { 
	int cpu;
	int thermalmib[6] = { 6, 302, 275, 259, 256 };
	size_t mibsize, tempsize;
	static char temps[MAXSTR];
	static char buf[32];
	double tz0;

	cpu = 0; 
	mibsize = 6;
	tempsize = sizeof(buf);

	if (sysctl(thermalmib, mibsize, &tz0, &mibsize, NULL, 0) < 0) { 
		fprintf(stderr, "ERR: sysctl(3): %s: got %G\n", strerror(errno), tz0);
		fprintf(stderr, "sysctl(%d.%d.%d.%d.%d.%d, %lu, %p, %p, NULL, 0) failed, trying sysctlbyname()\n",
				            thermalmib[0], thermalmib[1], thermalmib[2], thermalmib[3], thermalmib[4], thermalmib[5],
										mibsize, &tz0, &mibsize);
		if (sysctlbyname("hw.acpi.thermal.tz0.temperature", &buf, &mibsize, NULL, 0) < 0) {
				fprintf(stderr, "ERR: %s: got %G\n", strerror(errno), tz0);
		} else {
			fprintf(stdout, "buf: %G\n", tz0);
		}
		return(buf);
	}
	return(buf);
}

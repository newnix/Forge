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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXSTR 1024

char *gettemps(int ncpu);

int
main(int ac, char **av) { 
	int  mib[6] = { 0, 0, 0, 0, 0 };
	size_t miblen;

	miblen = sizeof(mib);

	for (++av; *av != NULL; av++) { 
		if (sysctlnametomib(*av, mib, &miblen) == -1) { 
			fprintf(stderr, "sysctlnametomib(%s) failed!\n", *av);
			break;
		}
		fprintf(stdout,"%s = %d.%d.%d.%d.%d.%d\n", *av, mib[0], mib[1], mib[2], mib[3], mib[4], mib[5]);
		memset(mib, 0, miblen);
	}

/* 
 * this part actually tries to get the cpu temp info
 */
	int mib2[2] = { CTL_HW, HW_NCPU };
	int ncpu;
	miblen = sizeof(mib2);

	/* for some reason this is returning 8 instead of 4, maybe a HT thing? */
	sysctl(mib2, sizeof(mib2), &ncpu, &miblen, NULL, 0);
		fprintf(stderr,"got %d cores\n", ncpu);
		sleep(3);
		char *test = gettemps(ncpu);
		fprintf(stdout, "%d cores scanned:\n\t%s\n", ncpu, test);
		return(0);
	//} else {
	//	fprintf(stderr, "Got %d CPU cores returned, but errors were encountered\n", ncpu);
	//	return(-1);
	//}
}

char *
gettemps(int ncpu) { 
	int cpu;
	int thermalmib[6] = { 6, 278, 0, 256 };
	size_t mibsize;
	double temp;
	static char temps[MAXSTR];
	char buf[32];

	cpu = 0; 
	mibsize = sizeof(thermalmib);

	for (; cpu < ncpu; cpu++) { 
		thermalmib[2] = cpu;
		/* query only requires no newp/newlen */
		if (sysctl(thermalmib, mibsize, &temp, &mibsize, NULL, 0) == -1) { 
			fprintf(stderr, "Can't get temp of CPU[%d]!\n", cpu);
		}
		fprintf(stdout, "CPU %d: %0.2f | \n", cpu, temp);
		/* unlikely to ever overrun */
		snprintf(buf, sizeof(buf), "C[%d]: %0.2f | ", cpu, temp);
		strlcat(temps, buf, MAXSTR);
	}

	return(temps);
}

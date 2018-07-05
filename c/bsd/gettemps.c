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

#define MAXSTR 1024

char *gettemps(int ncpu);

int
main(int ac, char **av) { 
	int ncpu, mib[6] = { 0, 0, 0, 0, 0, 0 };
	size_t cpusize, miblen;

	cpusize = sizeof(ncpu);
	miblen = sizeof(mib);
	ncpu = 0;

	for (++av; *av != NULL; av++) { 
		sysctlnametomib(*av, mib, &miblen);
		fprintf(stdout,"%s = %d.%d.%d.%d.%d.%d\n", *av, mib[0], mib[1], mib[2], mib[3], mib[4], mib[5]);
		memset(mib, 0, miblen);
	}

/* 
 * this part actually tries to get the cpu temp info
 */
	mib[0] = 6, mib[1] = 3, mib[2] = 0, mib[3] = 0, mib[4] = 0, mib[5] = 0;
	sysctl(mib, miblen/2, &ncpu, &cpusize, &ncpu, cpusize);
	char *test = gettemps(ncpu);
	fprintf(stdout, "%d cores scanned:\n\t%s\n", ncpu, test);
	return(0);
}

char *
gettemps(int ncpu) { 
	int cpu;
	int thermalmib[5] = { 6, 278, 0, 256, 0 };
	size_t mibsize, oldlen, newlen;
	double oldtemp, newtemp;
	static char temps[MAXSTR];
	char buf[32];

	mibsize = sizeof(thermalmib);
	cpu = 0; 
	newlen = oldlen = sizeof(oldtemp);

	for (; cpu < ncpu; cpu++) { 
		thermalmib[2] = cpu;
		sysctl(thermalmib, mibsize, &oldtemp, &oldlen, &newtemp, newlen);
		fprintf(stdout, "CPU %d: %.2f | %.2f\n", cpu, oldtemp, newtemp);
		/* unlikely to ever overrun */
		snprintf(buf, sizeof(buf), "core[%d]: %0.2f ", cpu, newtemp);
		strlcat(temps, buf, MAXSTR);
	}

	return(temps);
}

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
	int mib[6] = { 0, 0, 0, 0, 0, 0 };
	size_t miblen;

	miblen = sizeof(mib);
	for (++av; *av != NULL; av++) { 
		sysctlnametomib(*av, mib, &miblen);
		fprintf(stdout,"%s = %d.%d.%d.%d.%d.%d\n", *av, mib[0], mib[1], mib[2], mib[3], mib[4], mib[5]);
		memset(mib, 0, miblen);
	}
	char *test = gettemps(4);
	fprintf(stdout, "%s\n", test);
	return(0);
}

char *
gettemps(int ncpu) { 
	int cpu, offset;
	int thermalmib[5] = { 6, 278, 0, 256, 0 };
	size_t mibsize, oldlen, newlen;
	double oldtemp, newtemp;
	static char temps[MAXSTR];

	mibsize = sizeof(thermalmib);
	cpu = 0; 
	newlen = oldlen = MAXSTR;

	for (; cpu < ncpu; cpu++) { 
		thermalmib[3] = cpu;
		sysctl(thermalmib, mibsize, &oldtemp, &oldlen, &newtemp, newlen);
		fprintf(stdout, "CPU %d: %f | %f\n", cpu, oldtemp, newtemp);
		offset = snprintf(temps, MAXSTR, "%f | %f ", oldtemp, newtemp);
		*temps += (offset - 1);
	}

	return(temps);
}

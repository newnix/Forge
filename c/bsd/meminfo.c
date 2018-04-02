/* 
 * Copyright (c) 2017-2018, Exile Heavy Industries
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

#include <sys/types.h>
#include <sys/sysctl.h>

#include <kvm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int meminfo(uint8_t units);
void run_help(void);
double totalmem(uint8_t units);

extern char *__progname;

/* 
 * this should act similar to free(1) on Linux systems
 */
int
main(int argc, char **argv) {
	uint8_t units;
	char opt;

	units = 0;

	while ((getopt(argc,argv,"hkmgt")) != -1) {
		switch(opt) {
			case 'h':
				run_help();
				return(0);
			case 'k': /* display KiB */
				units ^= 0x0001;
				break;
			case 'm': /* display MiB */
				units ^= 0x0002;
				break;
			case 'g': /* display GiB */
				units ^= 0x0004;
				break;
			case 't': /* display TiB */
				units ^= 0x0008;
				break;
			default: /* Print usage info */
				break;
		}
	}
	fprintf(stderr,"units:\t%d\n",units);
	if (units == 0) { 
		run_help();
		return(0);
	} else { 
		meminfo(units);
	}
	return(0);
}

int
meminfo(uint8_t units) {
	totalmem(units);
	return(0);
}

void
run_help(void) {
	fprintf(stdout,"%s: Print memory usage\n",__progname);
	fprintf(stdout,"\t-h\tThis text\n");
	fprintf(stdout,"\t-k\tUse Kilobytes for output\n");
	fprintf(stdout,"\t-m\tUse Megabytes for output\n");
	fprintf(stdout,"\t-g\tUse Gigabytes for output\n");
	fprintf(stdout,"\t-t\tUse Terabytes for output\n");
}

double
totalmem(uint8_t units) { 
	int i, mib[4];
	size_t len;
	void *memory;

	sysctlnametomib("hw.physmem",mib,&len);
	if (sysctl(mib, 4, memory, &len, NULL, 0) == -1) { 
		perror("sysctl");
	} else { 
		printf("Total Memory: %d\n",(int)memory);
	}
	return(0);
}

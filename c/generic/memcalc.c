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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* simple utility to calculate human-friendly memory size from the pagesize */
double memsize(double pagesize, double pages);
double mem_gb(double memsize);
double mem_kb(double memsize);
double mem_mb(double memsize);
void print_meminfo(double memsize);
void print_shminfo(double total, double pagesize);
void run_help(void);

extern const char *__progname;

int
main(int argc, char **argv) {
	int opt;
	double pagesize, pages, total;

	opt = 0;
	pagesize = pages = 0;

	while ((opt = getopt(argc, argv, "hp:s:t:")) != -1) { 
		switch(opt) { 
			case 'h':
				run_help();
				break;
			case 'p':
				pages = strtol(optarg, NULL, 10);
				break;
			case 's':
				pagesize = atol(optarg);
				break;
			case 't':
				total = atol(optarg);
				break; 
		}
	}
	if (pages != 0 && pagesize != 0) { 
		print_meminfo(memsize(pagesize, pages));
	} else { 
		if (total != 0 && pagesize != 0) { 
			print_shminfo(total, pagesize);
		}
	}
	return(0);
}

double
memsize(double pagesize, double pages) {
	return(pagesize * pages);
}

double
mem_gb(double memsize) { 
	/* divide by 1024^3 */
	return(memsize/1073741824);
}

double
mem_kb(double memsize) { 
	return(memsize/1024);
}

double
mem_mb(double memsize) {
	return(memsize/1048576);
}

void
print_meminfo(double memsize) {
	fprintf(stdout,"%.3F bytes is:\n",memsize);
	fprintf(stdout,"\t%.3F KiB\n\t%.3F MiB\n\t%.3F GiB\n",mem_kb(memsize), mem_mb(memsize), mem_gb(memsize));
}

void
print_shminfo(double memsize, double pagesize) { 
	fprintf(stdout,"Target of %.3FGiB:\n",memsize);
	fprintf(stdout,"\t%.3F MiB\n\t%.3F KiB\n\t%.3F B\n",(memsize * 1024), (memsize * 1048576), (memsize * 1073741824));
}

void
run_help(void) {
	fprintf(stdout,"%s: Simple utility to get memory size information in a human-readable format\n",__progname);
	fprintf(stdout,"\t-h\tThis help text\n");
	fprintf(stdout,"\t-p\tNumber of memory pages\n");
	fprintf(stdout,"\t-s\tMemory page size\n");
	fprintf(stdout,"\t-t\tCalculate from a desired total (only accepts gigabyte sizes right now)\n");
}

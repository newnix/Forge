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
uint64_t memsize(uint64_t pagesize, uint64_t pages);
uint64_t mem_gb(uint64_t memsize);
uint64_t mem_kb(uint64_t memsize);
uint64_t mem_mb(uint64_t memsize);
void print_meminfo(uint64_t memsize);
void print_shminfo(uint64_t total, uint64_t pagesize);
void run_help(void);

extern const char *__progname;

int
main(int argc, char **argv) {
	int opt;
	uint64_t pagesize, pages, total;

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
		if (total != 0) { 
			print_shminfo(total, pagesize);
		}
	}
	return(0);
}

uint64_t
memsize(uint64_t pagesize, uint64_t pages) {
	return(pagesize * pages);
}

uint64_t
mem_gb(uint64_t memsize) { 
	/* divide by 1024^3 */
	return(memsize/1073741824);
}

uint64_t
mem_kb(uint64_t memsize) { 
	return(memsize/1024);
}

uint64_t
mem_mb(uint64_t memsize) {
	return(memsize/1048576);
}

void
print_meminfo(uint64_t memsize) {
	fprintf(stdout,"%lu bytes is:\n",memsize);
	fprintf(stdout,"\t%lu KiB\n\t%lu MiB\n\t%lu GiB\n",mem_kb(memsize), mem_mb(memsize), mem_gb(memsize));
}

void
print_shminfo(uint64_t memsize, uint64_t pagesize) { 
	fprintf(stdout,"Target of %luGB requires:\n",memsize);
	fprintf(stdout,"\tkern.ipc.shmall=%lu\n",((memsize * 1073741824) / pagesize));
}

void
run_help(void) {
	fprintf(stdout,"%s: Simple utility to get memory size information in a human-readable format\n",__progname);
	fprintf(stdout,"\t-h\tThis help text\n");
	fprintf(stdout,"\t-p\tNumber of memory pages\n");
	fprintf(stdout,"\t-s\tMemory page size\n");
	fprintf(stdout,"\t-t\tCalculate from a desired total (only accepts gigabyte sizes right now)\n");
}

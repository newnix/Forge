/* Copyright (c) 2017-2018, Exile Heavy Industries
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

extern char **environ;
extern char *__progname;

int nxenv(uint8_t flags);
void run_help(void);

int
main(int argc, char **argv) {
	char *envvar, *value;
	int ch;
	/* simple bitmaps for args */
	uint8_t flags;

	/* variable initialization */
	ch = flags = 0;
	envvar = 0;
	value = 0;
	
	/* create a buffer to hold up to INT_MAX chars for a new env var */
	if((envvar = calloc((size_t) 1, (size_t) 65535)) == NULL) {
		fprintf(stderr,"Could not allocate memory for temp buffer!\n");
		return(1);
	}
	if((value = calloc((size_t) 1, (size_t) 65535)) == NULL) {
		fprintf(stderr,"Could not allocate memory for temp buffer!\n");
		return(1);
	}

	while((ch = getopt(argc, argv, "d:hs:v:0")) != -1) {
		switch(ch) {
			case 'd':
				flags ^= 0x0001;
				strncpy(envvar,optarg,65535);
				break;
			case 'h':
				flags ^= 0x0010;
				run_help();
				break;
			case 's':
				strncpy(envvar,optarg,65535);
				flags ^= 0x0002;
				break;
			case 'v':
				strncpy(value,optarg,65535);
				flags ^= 0x0004;
				break;
			case '0':
				flags ^= 0x0008;
				break;
			default:
				break;
		}
	}

	nxenv(flags);
	/* release the memory before we exit */
	free(envvar);
	free(value);
	return(0);
}

int
nxenv(uint8_t flags) {
	/* useful for verifying the value set in the bitmap flags
	fprintf(stderr,"flags =\t%X\n",flags); 
	*/
	if(flags & 0x0000) {
		for(int i = 0; environ[i] != NULL; i++) {
			fprintf(stdout,"%p\t%s\n",&environ[i],environ[i]);
		}
	}
	return(0);
}

void
run_help(void) {
	fprintf(stdout,"%s: New Exile's env(1)\n",__progname);
	fprintf(stdout,"\t-d\tDelete an environmental variable\n");
	fprintf(stdout,"\t-h\tThis help text\n");
	fprintf(stdout,"\t-s\tSet the value of an environmental variable\n");
	fprintf(stdout,"\t-v\tValue of the environmental variable to be set\n");
}

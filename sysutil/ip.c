/* 
 *	Copyright (c) 2017-2018, Exile Heavy Industries
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted (subject to the limitations in the disclaimer
 *	below) provided that the following conditions are met:
 *
 *	* Redistributions of source code must retain the above copyright notice, this
 *		list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation
 *		and/or other materials provided with the distribution.
 *
 *	* Neither the name of the copyright holder nor the names of its contributors may be used
 *		to endorse or promote products derived from this software without specific
 *		prior written permission.
 *
 *	NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
 *	LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *	GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *	OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 *	DAMAGE.
 */

#include <stdio.h>
#include <unistd.h>

#define IP4 0x0001
#define IP6 0x0002
#define DECMASK 0x0004
#define HELP 0x0008
#define HEXMASK 0x0010
#define LISTHOSTS 0x0020
#define OCTMASK 0x0040
#define IP4SEP '.'
#define IP6SEP ':'

char *__progname;

int brdcast(uint8_t *addr);
int cook(uint8_t flags, int optind, char **argv);
int decmask(uint8_t *addr);
int hexmask(uint8_t *addr);
int hostaddrs(uint8_t *addr);
int netwkaddr(uint8_t *addr);
int octmask(uint8_t *addr);
void usage(void);

int 
main(int argc, char **argv) { 
	uint8_t ip4[4];
	uint8_t ip6[16];
	uint8_t flags, mask;
	int ch;

	*ip4 = 0;
	*ip6 = 0;
	ch = flags = mask = 0; 

	while ((ch = getopt(argc, argv, "46dhlox")) != -1) { 
		switch(ch) { 
			case '4':
				flags ^= IP4;
				break;
			case '6':
				flags ^= IP6;
				break;
			case 'd':
				flags ^= DECMASK;
				break;
			case 'h':
				flags ^= HELP;
				break;
			case 'l':
				flags ^= LISTHOSTS;
				break;
			case 'o':
				flags ^= OCTMASK;
				break;
			case 'x':
				flags ^= HEXMASK;
				break;
			default:
				flags ^= flags;
				break;
		}
	}

	/* Parse the arguments */
	cook(flags, optind, argv);

	return(0);
}

int
brdcast (uint8_t *addr) {	
	return(0);
}

int 
cook(uint8_t flags, int optind, char **argv) { 
	if (flags == HELP || argv[1] == 0) { 
		usage();
		return(0);
	}
	return(0);
}

void
usage(void) { 
	fprintf(stdout,"%s: Simple IP address and netmask calculator\n",__progname);
	fprintf(stdout,"\t-4\tExplicitly operate with the ip4 address space\n"
								 "\t-6\tExplicitly operate with the ip6 address space\n"
								 "\t-d\tOnly show the decimal representation of the netmask\n"
								 "\t-h\tThis help message\n"
								 "\t-l\tList all possible host addresses, not just the range\n"
								 "\t-o\tOnly show the octal representation of the netmask\n"
								 "\t-x\tOnly show the hexadecimal representation of the netmask\n"
								 "\n\tEx: ip 192.168.0.0/4\n");
}

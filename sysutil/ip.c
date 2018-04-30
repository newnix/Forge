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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IP4 0x0020
#define IP6 0x0040
#define DECMASK 0x0001
#define HELP 0x0002
#define HEXMASK 0x0004
#define LISTHOSTS 0x0008
#define OCTMASK 0x0010
#define IP4SEP '.'
#define IP6SEP ':'

char *__progname;

int brdcast(uint8_t *addr);
uint8_t * buildaddr(char *arg, int addrclass);
int cook(uint8_t flags, int optind, char **argv);
int decmask(uint8_t *addr);
int hexmask(uint8_t *addr);
int hostaddrs(uint8_t *addr, int list);
int netwkaddr(uint8_t *addr);
int octmask(uint8_t *addr);
void usage(void);

int 
main(int argc, char **argv) { 
	uint8_t flags;
	int ch;

	ch = flags = 0; 

	while ((ch = getopt(argc, argv, "46dhlox")) != -1) { 
		/* *mask flags are mutually exclusive */
		switch(ch) { 
			case 'd':
				/* 0000 0001 */
				flags ^= DECMASK;
				break;
			case 'h':
				/* 0000 0010 */
				flags ^= HELP;
				break;
			case 'l':
				/* 0100 0100 */
				flags ^= LISTHOSTS;
				break;
			case 'o':
				/* 0000 1000 */
				flags ^= OCTMASK;
				break;
			case 'x':
				/* 0001 0000 */
				flags ^= HEXMASK;
				break;
			default:
				flags ^= flags;
				break;
		}
	}

	/* Parse the arguments */
	return(cook(flags, optind, argv));
}

int
brdcast (uint8_t *addr) {	
	return(0);
}

uint8_t *
buildaddr(char *arg, int addrclass) { 
	static uint8_t addr[17];
	int i,j,k;
	char buf[5];

	*addr = *buf = k = 0;

	if (addrclass == IP4) { 
		for (i = 0,j = 0; arg[i] != 0; i++) { 
			if (arg[i] <= 57 && arg[i] >= 48) { 
				buf[j] = arg[i];
				j++;
			} else if (arg[i] == '.') { 
				buf[j++] = 0;
				j ^= j;
				addr[k] = (uint8_t)atoi(buf); 
				k++;
				memset(buf, 0, sizeof(buf));
			} else if (arg[i] == '/') { 
				/* this is where the subnet mask is set */
				buf[j++] = 0;
				addr[k] = atoi(buf);
				j ^= j; /* reset j */
				k++;
				memset(buf, 0, sizeof(buf));
				buf[0] = arg[i+1];
				buf[1] = arg[i+2];
				buf[3] = 0;
				addr[k] = (uint8_t)atoi(buf);
			}
		}
		fprintf(stderr,"%u.%u.%u.%u/%d\n",addr[0],addr[1],addr[2],addr[3],addr[4]);
		return(addr);
	} else if (addrclass == IP6) { 
		return(addr);
	}
	return((uint8_t *) 1);
}

int 
cook(uint8_t flags, int optind, char **argv) { 
	/* Additional entry in the array is for the mask bits */
	int addrclass, list;
	uint8_t *ip;

	addrclass = list = 0;
	if ((ip = calloc(17, sizeof(uint8_t))) == NULL) { 
		fprintf(stderr,"ERR: Failed to allocate memory!\n");
		return(1);
	}

	if (flags == HELP || argv[1] == 0) { 
		usage();
		free(ip);
		return(0);
	} else { 
		if (strchr(argv[optind], IP4SEP) == NULL && strchr(argv[optind], IP6SEP) == NULL) { 
			fprintf(stderr,"%s: invalid IP address!\n",argv[optind]);
			free(ip);
			return(1);
		} else { 
			addrclass = ((strchr(argv[optind], IP4SEP) != NULL)) ? IP4 : IP6 ;
			ip = buildaddr(argv[optind], addrclass);
		}

		switch(flags & 255) { 
			/* at this point, we're only deciding which functions we're running */
			case 0:
				/* this should be the same as the default case, run all functions */
				hostaddrs(ip,list);
				brdcast(ip);
				netwkaddr(ip);
				decmask(ip);
				octmask(ip);
				hexmask(ip);
				break;
			case DECMASK:
				hostaddrs(ip,list);
				brdcast(ip);
				netwkaddr(ip);
				decmask(ip);
				break;
			case HEXMASK:
				hostaddrs(ip,list);
				brdcast(ip);
				netwkaddr(ip);
				hexmask(ip);
				break;
			case LISTHOSTS:
				list = 1;
				break;
			case OCTMASK:
				hostaddrs(ip,list);
				brdcast(ip);
				netwkaddr(ip);
				octmask(ip);
				break;
			case DECMASK|LISTHOSTS:
				hostaddrs(ip,list);
				brdcast(ip);
				netwkaddr(ip);
				decmask(ip);
				list = 1;
				break;
			case HEXMASK|LISTHOSTS:
				hostaddrs(ip,list);
				brdcast(ip);
				netwkaddr(ip);
				hexmask(ip);
				list = 1;
				break;
			case OCTMASK|LISTHOSTS:
				hostaddrs(ip,list);
				brdcast(ip);
				netwkaddr(ip);
				octmask(ip);
				list = 1;
				break;
			default:
				hostaddrs(ip,list);
				brdcast(ip);
				netwkaddr(ip);
				decmask(ip);
				octmask(ip);
				hexmask(ip);
				break;
		}
	}
	/* free(ip); Not sure at the moment what happened, but this was causing an assertion failure */
	return(0);
}

int
decmask(uint8_t *addr) { 
	/* we need to check for an ip6 address first, and if that fails, use the ip4 location */
	int i,netclass;
	uint8_t maskbits;
	uint8_t mask[17];

	*mask = maskbits = netclass = 0;
	/* 
	 * The netmask has to be between 32 and 128 bytes total, depending
	 * on which protocol this is. 
	 *
	 * The most efficient way to get this is by having a literal bitmask 
	 * that can be recycled per "word" in each address field.
	 */

	maskbits = (addr[16] == 0) ? addr[4] : addr[16];
	/*
	 * Assuming an ip4 address, the mask would be 4*8b, or 32bits,
	 * one uint on most architectures.While an ip6 address would be 16*8 or 128b
	 * which is probably a unsigned long long on most architectures
	 * so if I can ignore the top 96 bits of a uint128_t, then we can just use that
	 * or stick with the uint8_t and do a shift on the remainder bits
	 * for our last octet mask.
	 */
	for (i = 0; i < (maskbits / 8); i++) { 
		mask[i] = ~0;
	}
	if ((maskbits % 8) > 0 ) { 
		mask[i] = ((~0 >> ( 8 - (maskbits % 8))) << (8 - (maskbits % 8)));
		i++;
	}

	mask[i] = 0;
	fprintf(stderr,"Netmask (decimal): %u.%u.%u.%u\n",mask[0],mask[1],mask[2],mask[3]);
	return(0);
}

int
hexmask(uint8_t *addr) { 
	return(0);
}

int
hostaddrs(uint8_t *addr, int list) { 
	return(0);
}

int
netwkaddr(uint8_t *addr) { 
	return(0);
}

int
octmask(uint8_t *addr) { 
	return(0);
}

void
usage(void) { 
	fprintf(stdout,"%s: Simple IP address and netmask calculator\n",__progname);
	fprintf(stdout,"\t-d\tOnly show the decimal representation of the netmask\n"
								 "\t-h\tThis help message\n"
								 "\t-l\tList all possible host addresses, not just the range\n"
								 "\t-o\tOnly show the octal representation of the netmask\n"
								 "\t-x\tOnly show the hexadecimal representation of the netmask\n"
								 "\n\tEx: ip 192.168.0.0/4\n"
								 "\t    ip fe80::6a05:caff:fe3f:a9da/64\n");
}

/* 
 *	Copyright (c) 2018, Exile Heavy Industries
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
#include <stdint.h> /* ensure uint8_t and similar are available */
#include <string.h>
#include <unistd.h>

#define DECMASK 0x0001
#define HELP 0x0002
#define HEXMASK 0x0004
#define LISTHOSTS 0x0008
#define OCTMASK 0x0010
#define IP4SEP '.'
#define IP6SEP ':'

char *__progname;

/*
 * single, 66 Byte struct to more efficiently pass 
 * information around, also removes the need to copy local variables
 */
typedef struct addrinfo { 
		uint8_t addr[16];
		uint8_t mask[16];
		uint8_t ntwk[16];
		uint8_t bdst[16];
		uint8_t maskbits;
		uint8_t class;
} addr;

static int brdcast(addr *addr);
static int buildaddr(char *arg, addr *ip);
static int cook(uint8_t flags, int optind, char **argv);
static int hostaddrs(addr *addr);
static int netmask(addr *addr);
static int netwkaddr(addr *addr);
static int printinfo(addr *addr);
static void usage(void);

int 
main(int argc, char **argv) { 
	uint8_t flags;
	int ch;

	ch = flags = 0; 

	while ((ch = getopt(argc, argv, "dhlox")) != -1) { 
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

static int
brdcast (addr *addr) {	
	int i; 

	/* this is when all the host bits are set, so we should be able to just twiddle any leftover octets to get this working */
	for (i = 0; i < addr->class; i++) { 
		addr->mask[i] = ~addr->mask[i];
		addr->bdst[i] = (addr->addr[i] | addr->mask[i]); 
		addr->mask[i] = ~addr->mask[i];
	}
	return(0);
}

static int
buildaddr(char *arg, addr *ip) { 
	int i,j,k;
	char buf[5];

	*buf = k = 0;

	for (i = 0,j = 0; arg[i] != 0; i++) { 
		if (arg[i] <= 57 && arg[i] >= 48) { 
			buf[j] = arg[i];
			j++;
		} else if (arg[i] == '.') { 
			ip->class = 4;
			buf[j++] = 0;
			j ^= j;
			ip->addr[k] = (uint8_t)atoi(buf); 
			k++;
			memset(buf, 0, sizeof(buf));
		} else if (arg[i] == '/') { 
			/* this is where the subnet mask is set */
			buf[j++] = 0;
			ip->addr[k] = atoi(buf); /* write the last octet to ip->addr */
			j ^= j; /* reset j */
			k++;
			memset(buf, 0, sizeof(buf));
			/* get and write the subnet mask bits */
			buf[0] = arg[i+1];
			buf[1] = arg[i+2];
			buf[3] = 0;
			ip->maskbits = (uint8_t)atoi(buf);
		}
	}
	return(0);
}

static int 
cook(uint8_t flags, int optind, char **argv) { 
	addr *ip;

	if ((ip = calloc(1, sizeof(ip))) == NULL) { 
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
			buildaddr(argv[optind], ip);
		}

		switch(flags & 255) { 
			case 0:
				/* this should be the same as the default case, run all functions */
				netmask(ip);
				brdcast(ip);
				netwkaddr(ip);
				printinfo(ip);
				break;
			case LISTHOSTS:
				netmask(ip);
				brdcast(ip);
				netwkaddr(ip);
				hostaddrs(ip);
			break;
			default:
				netmask(ip);
				brdcast(ip);
				netwkaddr(ip);
				hostaddrs(ip);
				break;
		}
	}
	free(ip);
	return(0);
}

static int
hostaddrs(addr *addr) {
	/*
	 * If list is nonzero, we're going to print out every address in the range
	 * otherwise, just print the summary, first host and last host
	 */
	return(0);
}

static int
netmask(addr *addr) { 
	int i;

	for (i = 0; i < (addr->maskbits / 8); i++) { 
		addr->mask[i] = ~0;
	}
	if ((addr->maskbits % 8) > 0 ) { 
		addr->mask[i] = ((~0 >> ( 8 - (addr->maskbits % 8))) << (8 - (addr->maskbits % 8)));
		i++;
	}
	addr->mask[i] = 0;
	return(0);
}

static int
netwkaddr(addr *addr) { 
	/* should pass in the netmask generated in netmask(), so it should be a simple bitwise operation */
	int i; 

	i = 0;

	for (i = 0; i < addr->class; i++) { 
		addr->ntwk[i] = (addr->addr[i] & addr->mask[i]);
	}
	return(0);
}

static int
printinfo(addr *addr) { 
	if (addr->class == 4) { 
		fprintf(stdout,
				"Address:\t%u.%u.%u.%u\n"
				"Netmask:\t%u.%u.%u.%u\n"
				"Hexmask:\t0x%X%X%X%X\n"
				"Octmask:\t0%o%o%o%o\n"
				"Network:\t%u.%u.%u.%u\n"
				"Broadcast:\t%u.%u.%u.%u\n"
				"IP Range:\t%u.%u.%u.%u - %u.%u.%u.%u\n",
				addr->addr[0],addr->addr[1],addr->addr[2],addr->addr[3],
				addr->mask[0],addr->addr[1],addr->addr[2],addr->addr[3],
				addr->mask[0],addr->mask[1],addr->mask[2],addr->mask[3], 
				addr->mask[0],addr->mask[1],addr->mask[2],addr->mask[3],
				addr->ntwk[0],addr->ntwk[1],addr->ntwk[2],addr->ntwk[3],
				addr->bdst[0],addr->bdst[1],addr->bdst[2],addr->bdst[3],
				addr->ntwk[0],addr->ntwk[1],addr->ntwk[2],(addr->ntwk[3] + 1),
				addr->bdst[0],addr->bdst[1],addr->bdst[2],(addr->bdst[3] - 1));
	}

	return(0);
}

static void
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

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

#define HELP 0x0002
#define LISTHOSTS 0x0008
#define IP4SEP '.'
#define IP6SEP ':'

char *__progname;

/*
 * single, 66 Byte struct to more efficiently pass 
 * information around, also removes the need to copy local variables
 * should be converted to using uint16_t for arrays so the ip6 info
 * is better preserved and presented, currently bit values are displayed
 * accurately, but values are misleading in decimal
 */
typedef struct addrinfo { 
		uint16_t addr[8];
		uint16_t mask[8];
		uint16_t ntwk[8];
		uint16_t bdst[8];
		uint8_t maskbits;
		uint8_t class;
} addr;

static int brdcast(addr *addr);
static int buildaddr(char *arg, addr *ip);
static int cook(uint8_t flags, char *args);
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

	while ((ch = getopt(argc, argv, "hl")) != -1) { 
		switch(ch) { 
			case 'h':
				/* 0000 0010 */
				flags ^= HELP;
				break;
			case 'l':
				/* 0100 0100 */
				flags ^= LISTHOSTS;
				break;
			default:
				flags ^= flags;
				break;
		}
	}

	/* Parse the arguments */
	return(cook(flags, argv[optind]));
}

static int
brdcast (addr *addr) {	
	int i; 

	/* this is when all the host bits are set, so we should be able to just twiddle any leftover octets to get this working */
	for (i = 0; i < addr->class; i++) { 
		addr->mask[i] = ~addr->mask[i];
		addr->bdst[i] = (addr->class == 4) ? (addr->addr[i] | (addr->mask[i] ^ 0xFF00)) : (addr->addr[i] | addr->mask[i]); 
		addr->mask[i] = ~addr->mask[i];
	}
	return(0);
}

static int
buildaddr(char *arg, addr *ip) { 
	int i,j,k;
	char buf[5];
	uint8_t hexval[4];

	memset(hexval,0,sizeof(hexval));
	*buf = k = 0;

	if (ip->class == 4) {
		for (i = 0,j = 0; arg[i] != 0; i++) { 
			if (arg[i] <= 57 && arg[i] >= 48) { 
				buf[j] = arg[i];
				j++;
			} else if (arg[i] == IP4SEP) { 
				buf[j++] = 0;
				j ^= j;
				ip->addr[k] = (uint16_t)atoi(buf); 
				k++;
				memset(buf, 0, sizeof(buf));
			} 
			if (arg[i] == '/') { 
				/* this is where the subnet mask is set */
				buf[j++] = 0;
				ip->addr[k] = (uint16_t)atoi(buf); /* write the last octet to ip->addr */
				j ^= j; /* reset j */
				k++;
				memset(buf, 0, sizeof(buf));
				/* get and write the subnet mask bits */
				buf[0] = arg[i+1];
				buf[1] = arg[i+2];
				buf[3] = 0;
				ip->maskbits = (uint16_t)atoi(buf);
				memset(buf, 0, sizeof(buf));
			} 
			/* if no / was encountered, make sure we flush *buf to the struct */
			if (atoi(buf) > 0) { 
				ip->addr[k] = (uint16_t)atoi(buf);
			}
		}
	} else if (ip->class == 8) {
		for (i = 0,j = 0; arg[i] != 0; i++) {
			if (arg[i] <= 57 && arg[i] >= 48) {
				buf[j] = arg[i]; 
				j++;
			} else if (arg[i] >= 97 && arg[i] <= 102) {
				buf[j] = (arg[i] - 32); 
				j++;
			} else if (arg[i] >= 65 && arg[i] <= 70) { 
				buf[j] = arg[i]; 
				j++;
			}
			/* this gets tricky, since ipv6 allows for "::" to compress a run of 0's */
			if (arg[i] == IP6SEP || arg[i + 1] == '/') {  
				for (j = 0; j < 5; j++) { 
					switch (buf[j]) { 
						/* should only have capitalized hex values */
						case 'A':
							hexval[j] = 10;
							break;
						case 'B':
							hexval[j] = 11;
							break;
						case 'C':
							hexval[j] = 12;
							break;
						case 'D':
							hexval[j] = 13;
							break;
						case 'E':
							hexval[j] = 14;
							break;
						case 'F':
							hexval[j] = 15;
							break;
						case '0':
							hexval[j] = 0;
							break;
						case '1':
							hexval[j] = 1;
							break;
						case '2':
							hexval[j] = 2;
							break;
						case '3':
							hexval[j] = 3;
							break;
						case '4':
							hexval[j] = 4;
							break;
						case '5':
							hexval[j] = 5;
							break;
						case '6':
							hexval[j] = 6;
							break;
						case '7':
							hexval[j] = 7;
							break;
						case '8':
							hexval[j] = 8;
							break;
						case '9':
							hexval[j] = 9;
							break;
						default:
							break;
					}
				}
				ip->addr[k] = (hexval[3] + (hexval[2] * 16) + (hexval[1] * 16 * 16) + (hexval[0] * 16 * 16 * 16));
				k++;
				j ^= j;
				memset(buf,0,sizeof(buf));
				memset(hexval,0,sizeof(hexval));
			}
			if (arg[i] == '/') {
				for (j = 0,i += 1; arg[i] != 0; i++) { 
					buf[j] = arg[i]; 
					j++;
				}
				ip->maskbits = (uint8_t)atoi(buf);
				break;
			}
		}
	}
	return(0);
}

static int 
cook(uint8_t flags, char *args) { 
	addr *ip;

	if ((ip = calloc(1, sizeof(ip))) == NULL) { 
		fprintf(stderr,"ERR: Failed to allocate memory!\n");
		return(1);
	}

	if (flags == HELP || *args == 0) { 
		usage();
		free(ip);
		/* show the contents of the addr struct */
		return(0);
	} else { 
		if (strchr(args, IP4SEP) == NULL && strchr(args, IP6SEP) == NULL) { 
			fprintf(stderr,"%s: invalid IP address!\n",args);
			free(ip);
			return(1);
		} 
		if (strchr(args, IP4SEP) != NULL) { 
			ip->class = 4; 
		} else if (strchr(args, IP6SEP) != NULL) { 
			ip->class = 8;
		}

		buildaddr(args, ip);

		switch(flags) { 
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
				printinfo(ip);
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
	uint16_t zero;

	zero = 0;
	/* assume a mask of all 1's if none was given */
	if (addr->maskbits == 0) {
		addr->maskbits = (addr->class == 4) ? 32 : 128;
	}

	for (i = 0; i < (addr->maskbits / 16); i++) { 
		/* XOR out the top 8 bits if we're using ipv4 */
		addr->mask[i] = (addr->class == 4) ? ~zero ^ 0xFF00 : ~zero;
	}
	if ((addr->maskbits % 8) > 0 ) { 
		addr->mask[i] = (addr->class == 4) ? ((~zero >> ( 16 - (addr->maskbits % 16))) << (16 - (addr->maskbits % 16))) & 0x00FF : ((~zero >> ( 16 - (addr->maskbits % 16))) << (16 - (addr->maskbits % 16)));
		i++;
	}
	addr->mask[i] = zero;
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

/* must find a better means of presenting this information */
static int
printinfo(addr *addr) { 
	if (addr->class == 4) { 
		fprintf(stdout,
				"Address:\t%u.%u.%u.%u\n"
				"Netmask:\t%u.%u.%u.%u\n"
				"Hexmask:\t0x%02X%02X%02X%02X\n"
				"Octmask:\t0%03o%03o%03o%03o\n"
				"Network:\t%u.%u.%u.%u\n"
				"Broadcast:\t%u.%u.%u.%u\n"
				"IP Range:\t%u.%u.%u.%u - %u.%u.%u.%u\n",
				addr->addr[0],addr->addr[1],addr->addr[2],addr->addr[3],
				addr->mask[0],addr->mask[1],addr->mask[2],addr->mask[3],
				addr->mask[0],addr->mask[1],addr->mask[2],addr->mask[3], 
				addr->mask[0],addr->mask[1],addr->mask[2],addr->mask[3],
				addr->ntwk[0],addr->ntwk[1],addr->ntwk[2],addr->ntwk[3],
				addr->bdst[0],addr->bdst[1],addr->bdst[2],addr->bdst[3],
				addr->ntwk[0],addr->ntwk[1],addr->ntwk[2],((addr->maskbits == 32) ? addr->addr[3] : (addr->ntwk[3] + 1)),
				addr->bdst[0],addr->bdst[1],addr->bdst[2],((addr->maskbits == 32) ? addr->addr[3] : (addr->bdst[3] - 1))); 
	} else { 
		printf("*addrinfo struct:\n"
				"Address:\t%04X:%04X:%04X:%04X:%04X:%04X:%04X:%04X\n"
				"Netmask:\t%u:%u:%u:%u:%u:%u:%u:%u\n"
				"Hexmask:\t%04X:%04X:%04X:%04X:%04X:%04X:%04X:%04X\n"
				"Octmask:\t%03o:%03o:%03o:%03o:%03o:%03o:%03o:%03o\n"
				"Network:\t%04X:%04X:%04X:%04X:%04X:%04X:%04X:%04X\n"
				"Broadcast:\t%04X:%04X:%04X:%04X:%04X:%04X:%04X:%04X\n"
				"IP Range:\t%04X:%04X:%04X:%04X:%04X:%04X:%04X:%04X - %04X:%04X:%04X:%04X:%04X:%04X:%04X:%04X\n"
				"addr->class:\t%u\n"
				"addr->maskbits:\t%u\n",
				addr->addr[0],addr->addr[1],addr->addr[2],addr->addr[3],addr->addr[4],addr->addr[5],addr->addr[6],addr->addr[7],
				/* netmask */
				addr->mask[0],addr->mask[1],addr->mask[2],addr->mask[3],addr->mask[4],addr->mask[5],addr->mask[6],addr->mask[7],
				/* conversions */
				addr->mask[0],addr->mask[1],addr->mask[2],addr->mask[3],addr->mask[4],addr->mask[5],addr->mask[6],addr->mask[7],
				addr->mask[0],addr->mask[1],addr->mask[2],addr->mask[3],addr->mask[4],addr->mask[5],addr->mask[6],addr->mask[7],
				/* network */
				addr->ntwk[0],addr->ntwk[1],addr->ntwk[2],addr->ntwk[3],addr->ntwk[4],addr->ntwk[5],addr->ntwk[6],addr->ntwk[7],
				/* broadcast */
				addr->bdst[0],addr->bdst[1],addr->bdst[2],addr->bdst[3],addr->bdst[4],addr->bdst[5],addr->bdst[6],addr->bdst[7],
				/* range */
				addr->ntwk[0],addr->ntwk[1],addr->ntwk[2],addr->ntwk[3],addr->ntwk[4],addr->ntwk[5],addr->ntwk[6],((addr->maskbits == 128) ? addr->addr[7] : (addr->ntwk[7] + 1)),
				addr->bdst[0],addr->bdst[1],addr->bdst[2],addr->bdst[3],addr->bdst[4],addr->bdst[5],addr->bdst[6],((addr->maskbits == 128) ? addr->addr[7] : (addr->bdst[7] - 1)),
				/* class */
				addr->class,
				/* maskbits */
				addr->maskbits
				);
	} 

	return(0);
}

static void
usage(void) { 
	fprintf(stdout,"%s: Simple IP address and netmask calculator\n",__progname);
	fprintf(stdout,"\t-h\tThis help message\n"
								 "\t-l\tList all possible host addresses, not just the range\n"
								 "\n\tEx: ip 192.168.0.0/24\n"
								 "\t    ip fe80::6a05:caff:fe3f:a9da/64\n");
}

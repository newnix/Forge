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

/* 
 * This is meant to be a utility similar to beadm(1) on FreeBSD/Illumos
 * however, I'd rather have it written in C than have a massive shell script.
 * So this should be an interesting exercise in getting familiar with hammer2's
 * snapshot feature and managing important system files. 
 *
 * Provided this project actually bears any results, DragonFly BSD development 
 * can proceed even faster as both vkernels and boot environments would 
 * make testing new builds almost completely painless
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* more inclusions are likely to follow, but at least these will be needed */
#include "dfbeadm.h"

int 
main(int argc, char **argv) { 
	/* obviously, this is where we get some basic data from the user */
	int ch;
	while((ch = getopt(argc,argv,"a:d:hlr:s:R:S:")) != -1) { 
		switch(ch) { 
			case 'a': 
				activate(optarg);
				break;
			case 'd':
				deactivate(optarg);
				break;
			case 'h':
				usage();
			case 'l':
				list();
				break;
			case 'r':
				rmsnap(optarg);
				break;
			case 'R':
				rmenv(optarg);
				break;
			case 's':
				snapfs(optarg);
				break;
			case 'S':
				snap(optarg);
				break;
			default:
				usage();
		}
	}
	return(0);
}

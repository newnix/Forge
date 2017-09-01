/*  Copyright (c) 2017, newnix
 *  All rights reserved.
 *  
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted (subject to the limitations in the disclaimer
 *  below) provided that the following conditions are met:
 *  
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  
 *  * Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *  
 *  NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
 *  LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 *  DAMAGE.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/stat.h>
#include <curl/curl.h>

extern char *__progname;

/*
 * This tool is meant to be a command-line unitility to subscribe to and download RSS feeds,
 * Ideally statically linked, and possibly even multithreaded to run multiple operations at once.
 * This should be possible to run in an automated fashion as well as interactively, so users can modify some settings.
 * This project is using the port www/rssroll as reference on how to work with this sort of data.
 */

int display_subs(void);
void fetch_subs(void);
void cook_args(void);
int update_subs(int feed_ids[]);
int add_sub(char *sub_name, char *sub_url);
int rm_sub(int feed_id);
int change_sub(int feed_id, char *old_name, char *new_name);
int build_dlq(int feed_ids[]);
int save_files(FILE *filename, char *dl_link);

int 
main(int argc, char *argv[]) {
	/* Get things started */
	char *directory; /* -d flag */
	char *label; /* -l flag */
	char *url; /* -U flag */
	char flags; /* 0000 0000 */

	while ((ch = getopt(argc, argv, "hd:l:uU:ar")) != -1) {
		switch (ch){
			case 'h':
				return(print_help());
			case 'a':
				flags &= 0x01;
				break;
			case 'd'
				strncpy(directory, optarg, 1024);
				break;
}

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

#include <assert.h>
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

/* 
 * Set of macros that create more easily remembered than their hex values
 */

#define ADD 0x01
#define DOWNLOAD 0x02
#define LIST 0x04
#define SETDIR 0x08
#define SETLABEL 0x10
#define UPDATE 0x20
#define SETURL 0x30
#define REMOVE 0x40

int display_subs(void);
void fetch_subs(void);
void cook_args(void);
int update_subs();
int add_sub(char *sub_name, char *sub_url);
int rm_sub(int feed_id);
int change_sub(int feed_id, char *old_name, char *new_name);
int build_dlq(int feed_ids[]);
int save_files(FILE *filename, char *dl_link);
int print_help(void);

int 
main(int argc, char *argv[]) {
	/* Get things started */
	char directory[1024]; /* -d flag */
	char label[1024]; /* -l flag */
	char url[1024]; /* -U flag */
	char ch; /* flag options */
	unsigned short int flags; /* 0000 0000 */
	int i;

	while ((ch = getopt(argc, argv, "hdD:lL:uU:ar")) != -1) {
		switch (ch){
			case 'h': /* ask for help */
				return(print_help());
			case 'a': /* add an entry */
				flags ^= 0x01;
				break;
			case 'd': /* download new entries */
				flags ^= 0x02;
				break;
			case 'l': /* list currently tracked rss feeds */
				flags ^= 0x04;
			case 'D': /* specify a download derictory */
				flags ^= 0x08;
				assert(strlcpy(directory, optarg, 1024) < 1025);
				break;
			case 'L': /* set a label for the entry */
				flags ^= 0x10;
				assert(strlcpy(label, optarg, 1024) < 1025);
				break;
			case 'u': /* update feeds */
				flags ^= 0x20;
				break;
			case 'U': /* the url of the feed */
				flags ^= 0x30;
				assert(strlcpy(url, optarg, 1024) < 1025);
				break;
			case 'r': /* remove a feed */
				flags ^= 0x40;
				break;
			default:
				break;
		}
	}

	cook_args();
	return 0;
}

void
cook_args(){
	unsigned short int comp; /* simple way of tracking values for bitmap comparisons */
	/* use the info with flags to determine what needs to be done */
	
}

int
print_help(){
	/* print the helpful message for the users */
	(void)fprintf(stdout,"%s:\t Track and download RSS feeds.\n",__progname);
	(void)fprintf(stdout,"\t-a\tAdd a new RSS entry\n");
	(void)fprintf(stdout,"\t-d\tDownload RSS updates\n");
	(void)fprintf(stdout,"\t-l\tList currently tracked RSS feeds\n");
	(void)fprintf(stdout,"\t-u\tUpdate tracked RSS feeds\n");
	(void)fprintf(stdout,"\t-r\tRemove a tracked RSS feed\n");
	(void)fprintf(stdout,"\t-D\tDownload new entries to the given directory\n");
	(void)fprintf(stdout,"\t-L\tGive an entry a short label, for ease of use\n");
	(void)fprintf(stdout,"\t-U\tSet the RSS entry's URL\n");
	(void)fprintf(stdout,"\n");
	return 0;
}

void
fetch_subs(){ 
	/* some libcurl stuff goes here to run through the tracked feeds and download episodes */
	/* each subscription should be able to go in its own directory for the sake of users organization preferences */
}

int
update_subs(){
	/* this should be handed off to libcurl to download new manifests of rss feeds */
}

int
add_sub(char *sub_name, char *sub_url){
	/* this should get some inforamation from the user in an interactive fashion to populate the subscription table */
	/*
	 * Essentially:
	 * insert into subscriptions (title, label, url, directory) values ();
	 */
}

int
rm_sub(int feed_id){
	/* interactively remove a sub from the table */
	/*
	 * Essentially:
	 * drop ${target} from subscriptions;
	 */
}

int
display_subs(){
	/* show the user what feeds they've subscribed to */
	/* 
	 * Essentially: 
	 * select title, label, episodes, new from subscriptions;
	 */
}

int
change_sub(int feed_id, char *old_name, char *new_name){
	/* Interactively allow the user to change the data in the database */
	/* once values are taken, essentially run an update on the database */
}

int
build_dlq(int *feed_ids){
	/* this will compile a list of downloads for the given list of feds to work with */
	/* should return the number of downloads completed */
}

int
save_files(FILE *filename, char *dl_link){
	/* this is meant to be called by build_dlq(), ideally in multiple threads or processes to maximize bandwidth utilization */
}

void
interactive_mode(){
	/* 
	 * This should basically act as a looped main(), 
	 * allowing the user to go through different operations without exiting
	 * This is only meant to run if there were no flags specified on the command-line.
	 * This may eventually be modified to use ncurses instead of raw text 
	 */
}

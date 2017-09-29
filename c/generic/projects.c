/*
 * Copyright (c) 2017, newnix
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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>

/*
 * This program will maintain and modify a "TODO" database, 
 * allowing you to easily check on projects as needed from the
 * command line. This should be built as a static binary to prevent 
 * potential issues with system updates. 
 */

extern char *__progname;
/* task database */
static sqlite3* taskdb;
/* debug help */
int debug = 0;

void run_help(void);
int db_reinit(void);
int db_init(const char *dbname);
int db_destroy(const char *dbname);
int task_add(char *name, char *desc, char *due, char *priority);
/* This can probably be done better with structs, but I'm not sure how to set that up yet */
int task_upd(int task, char *old_desc, char *old_due, char *old_priority, char *new_desc, char *new_due, char *new_priority);
int task_del(int task);
int task_list(int limit); /* default action */

int
main(int argc, char *argv[]) {
	/* create a couple of flags */
	unsigned short int aflag, eflag, kflag, lflag, nflag, pflag, rflag, uflag;
	char entry_name[32];
	char entry_desc[1024];
	char entry_priority[32];
	int entry_indx;
	char ch;
	
	/* initialize to 0 */
	aflag = eflag = kflag = lflag = nflag = pflag = rflag = uflag = entry_indx = 0;
	taskdb = NULL;

	while ((ch = getopt(argc, argv, "aep:r:u:nklh")) != -1) {
		switch (ch) {
			case 'a':
				aflag = 1;
				break;
			case 'e':
				eflag = 1;
				break;
			case 'p':
				pflag = 1;
				strncpy(entry_priority,optarg,16);
				break;
			case 'r':
				rflag = 1;
				entry_indx = (int)optarg;
				break;
			case 'u':
				uflag = 1;
				entry_indx = (int)optarg;
				break;
			case 'n':
				nflag = 1;
				break;
			case 'k':
				kflag = 1;
				break;
			case 'h':
				run_help();
				return 0;
			default:
				break;
		}
	}

	/* Check for some incompatible flags */
	if ((aflag == 1) && (rflag == 1)) {
		(void)fprintf(stderr,"ERR: a and r are mutually exclusive\n");
		return(2);
	}
	if ((rflag == 1) && (uflag == 1)) {
		(void)fprintf(stderr,"ERR: u and r are mutually exclusive\n");
		return(2);
	}
	if ((uflag == 1) && (aflag == 1)) {
		(void)fprintf(stderr,"ERR: a and u are mutually exclusive\n");
		return(2);
	}
	if ((kflag == 1) && (nflag == 1)) {
		(void)fprintf(stdout,"WARN: re-initializing task database, you will lose any existing tasks\n");
		db_reinit();
	}
	if (kflag == 1) 
		db_destroy("test");
	
	if (nflag == 1)
		db_init("test");

	return 0;
}

void
run_help(void){
 (void)fprintf(stdout,"%s:\n",__progname);
 (void)fprintf(stdout,"\t%s [-aenkh] | [-r id] | [-u id]  [-p priority]\n\n",__progname);
 (void)fprintf(stdout,"\tSimple command-line task list manager.\n");
 (void)fprintf(stdout,"\t\t-a\tCreate a new entry\n");
 (void)fprintf(stdout,"\t\t-e\tMark a created or updated entry as \"URGENT\"\n");
 (void)fprintf(stdout,"\t\t-k\tDestroy the currently existing database\n");
 (void)fprintf(stdout,"\t\t-n\tCreate a new database (existing database will be destroyed)\n");
 (void)fprintf(stdout,"\t\t-p\tSpecify a priority for a new or updated entry\n");
 (void)fprintf(stdout,"\t\t-r\tRemove an entry from the database\n");
 (void)fprintf(stdout,"\t\t-u\tUpdate a given entry\n");
 (void)fprintf(stdout,"\t\t-h\tThis text\n");
 (void)fprintf(stdout,"\tExample:\n\t\t%s -a -e\n",__progname);
}

int
db_reinit(void) {
	/* kill and rebuild the task database */
	db_destroy("test");
	db_init("test");
	return 0;
}

int
db_init(const char *dbname) {
	/* create the task database */
	int ret; /* check for return codes */
	(void)fprintf(stdout,"This is where we initialise %s\n",dbname);
	do {
		/* start the engine */
		if (ret = sqlite3_initialize()) {
			(void)fprintf(stderr,"Failed to initialize sqlite3 lib, ret:%d\n",ret);
			break;
		}
		/* open a db connection */
		if (ret = sqlite3_open(dbname, &taskdb)) {
			(void)fprintf(stderr,"Failed to open a connection to %s, ret:%d\n",dbname,ret);
			break;
		}
	} while (1 < 0);
	return 0;
}

int
db_destroy(const char *dbname) {
	/* destroy the database */
	/* this should ALWAYS be interactive */
	if (unlink(dbname) == 0) {
		return 0;
	} else {
		(void)fprintf(stderr,"ERR: Could not delete %s!\n",dbname);
		return 2;
	}
}

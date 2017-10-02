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
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>

#include "../kr/headers/charconv.h"

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
int db_reinit(const char *dbname);
int db_init(const char *dbname);
int db_destroy(const char *dbname);
int task_add_interactive(const char *dbname);
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
	const char *dbname;
	int entry_indx;
	char ch;
	
	/* initialize to 0 */
	aflag = eflag = kflag = lflag = nflag = pflag = rflag = uflag = entry_indx = 0;
	taskdb = NULL;
	dbname = "test";

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
		db_reinit(dbname);
	}

	/*
	 * These need to be moved into a more 
	 * comprehensive argument parser.
	 */
	if (kflag == 1) 
		db_destroy(dbname);
	
	if (nflag == 1)
		db_init(dbname);

	if (aflag == 1)
		task_add_interactive(dbname);	

	return 0;
}

void
run_help(void){
 (void)fprintf(stdout,"%s:\n",__progname);
 (void)fprintf(stdout,"\t%s [-aenkh] | [-r id] | [-u id]  [-p priority]\n\n",__progname);
 (void)fprintf(stdout,"\tSimple command-line task list manager.\n");
 (void)fprintf(stdout,"\t\t-a\tCreate a new entry (or more)\n");
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
db_reinit(const char *dbname) {
	/* kill and rebuild the task database */
	db_destroy(dbname);
	db_init(dbname);
	return 0;
}

int
db_init(const char *dbname) {
	/* create the task database */
	int ret; /* check for return codes */
	char *directory; /* I don't anticipate the directories being longer than this */
	(void)fprintf(stdout,"This is where we initialise task database:%s\n",dbname);
	do {
		/* start the engine */
		if ((ret = sqlite3_initialize()) != 0) {
			(void)fprintf(stderr,"Failed to initialize sqlite3 lib, ret:%d\n",ret);
			break;
		}
		if ((directory = malloc(sizeof(char) * 1024)) != NULL) {
			strncpy(directory, dirname(dbname), 1024);
			(void)fprintf(stdout,"Task database at %s/%s has been sucessfully created.\n", directory,  dbname);
		}
		/* open a db connection */
		if ((ret = sqlite3_open(dbname, &taskdb)) != 0) {
			(void)fprintf(stderr,"Failed to open a connection to %s, ret:%d\n",dbname,ret);
			break;
		}
		sqlite3_close(taskdb);
	} while (1 < 0);
	return 0;
}

int
db_destroy(const char *dbname) {
	/* destroy the database */
	/* this should ALWAYS be interactive */
	char *directory;

	/* get the directory name, to use an absolute path */
	if ((directory = malloc(sizeof(char) * 1024)) != NULL) {
		strncpy(directory, dirname(dbname), 1024);
		strncat(directory, '/', 1);
		strncat(directory, dbname, sizeof(dbname));
	}
		(void)fprintf(stdout,"new string: %s\n",directory);
	if (unlink(directory) == 0) {
		return 0;
	} else {
		(void)fprintf(stderr,"ERR: Could not delete %s!\n",directory);
		return 2;
	}
}

int
task_add_interactive(const char *dbname) {
	/*
	 * This function should provide an interactive propmt 
	 * to add new entries to the task database. This function 
	 * should recturn the number of tasks added. 
	 */
	char retry;
	sqlite3_open(dbname, &taskdb);
	
	/* verify that we didn't get a NULL value */
	do {
		/* ensure that 'retry' is initialized */
		retry = 0;
		sqlite3_open(dbname, &taskdb);
		if (taskdb == NULL) {
			fprintf(stdout,"Could not connect to database \"%s\", retry connection? [Y/n]\n",dbname);
			scanf("%c",&retry);
			/* try to ensure the input stream is clean */
			fpurge(stdin);
		}
	} while ((taskdb == NULL) || (upperc(retry) != 'N'));

	/* 
	 * Close the database connection if it exists 
	 */
	if (taskdb != NULL) {
		sqlite3_close(taskdb);
	}
	return 0;
}

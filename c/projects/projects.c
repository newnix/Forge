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

#include <ctype.h>
#include <err.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <pthread.h>
#include <unistd.h>

#include "charconv.h"

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
/* #define's didn't work well, trying external vars */
static size_t DBMAX = 512;
static size_t TASKSIZE = 32;
static size_t DESCSIZE = 1024;
static size_t TASKEXPR = 12;

/*
 * I should probably be using structs to 
 * track the query and similar data....
 */

struct entry {
	/* this allows for a linked list, which may or may not be useful */
	struct entry *previous;
	struct entry *next;
	unsigned long int index;
	char *table;
	char *task_name;
	char *task_desc;
	char *expiration;
	char urgent;
};

/* this of course, will require rewriting some existing code to work properly */


void run_help(void);
int db_create_tables(const char *dbname);
int db_destroy(const char *dbname);
int db_init(const char *dbname);
int db_reinit(const char *dbname);
int task_add_interactive(const char *dbname, const char *table_name);
int task_add(struct entry new_task);
/* This can probably be done better with structs, but I'm not sure how to set that up yet */
int task_upd(struct entry old_ent, struct entry new_ent);
/* this should probably use a union, to accept either the index or name */
int task_del(int task, const char *dbname);
int task_list(int limit, const char *dbname); /* default action */

int
main(int argc, char *argv[]) {
	/* create a couple of flags */
	unsigned short int aflag, dflag, eflag, kflag, lflag, nflag, pflag, rflag, tflag, uflag;
	char *homedir; /* It'd be ideal to default to ~/.${DBNAME} */
	char entry_name[32];
	char entry_priority[32];
	char entry_desc[1024];
	char dbname[DBMAX], dbtarget[DBMAX];
	char table_name[1024];
	int entry_indx;
	int ret; /* simple return value placeholder */
	struct entry task; /* should create an entry struct called "task" */
	char ch;
	
	/* initialize to 0 */
	aflag = dflag = eflag = kflag = lflag = nflag = pflag = rflag = tflag = uflag = entry_indx = 0;
	taskdb = NULL;
	/* this should be placed in the user's homedir, ideally as a dotfile to not clutter `ls` output */
	strncpy(dbtarget, "test.db", DBMAX);
	strncpy(table_name, "tasklist", 1024);
	/* get the $HOME */
	homedir = getenv("HOME");

	while ((ch = getopt(argc, argv, "ad:ep:r:u:T:nklh")) != -1) {
		switch (ch) {
			case 'a':
				aflag = 1;
				break;
			case 'e':
				eflag = 1;
				break;
			case 'd':
				dflag = 1;
				memset(dbname, 0, DBMAX);
				strncpy(dbtarget,optarg,DBMAX);
				break;
			case 'p':
				pflag = 1;
				strncpy(entry_priority,optarg,16);
				break;
			case 'r':
				rflag = 1;
				entry_indx = (int)optarg;
				/* task->index = (int)optarg; */
				break;
			case 'T':
				tflag = 1;
				strncpy(table_name, optarg, 1024);
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
				return(0);
			default:
				break;
		}
	}
	/* assemble the full path of dbname */
	snprintf(dbname, DBMAX, "%s/%s", homedir, dbtarget);

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
	} else if (kflag == 1) {
		db_destroy(dbname);
	} else if (nflag == 1) {
		db_init(dbname);
	}

	/*
	 * These need to be moved into a more 
	 * comprehensive argument parser.
	 */

	if (aflag == 1) {
		ret = task_add_interactive(dbname, table_name);	
		switch (ret) {
			case 1:
				fprintf(stdout,"Added %d task to the database.\n",ret);
				break;
			case 0:
				fprintf(stdout,"Added no new tasks to the database.\n");
				break;
			default:
				fprintf(stdout, "Added %d new tasks to the database.\n", ret);
				break;
		}
	}

	return(0);
}

void
run_help(void){
 (void)fprintf(stdout,"%s:\n",__progname);
 (void)fprintf(stdout,"\t%s [-aenkh] | [-r id] | [-u id]  [-p priority]\n\n",__progname);
 (void)fprintf(stdout,"\tSimple command-line task list manager.\n");
 (void)fprintf(stdout,"\t\t-a\tCreate a new entry (or more)\n");
 (void)fprintf(stdout,"\t\t-e\tMark a created or updated entry as \"URGENT\"\n");
 (void)fprintf(stdout,"\t\t-k\tDestroy the currently existing database\n");
 (void)fprintf(stdout,"\t\t-l\tList items from the database (default 10)\n");
 (void)fprintf(stdout,"\t\t-n\tCreate a new database (existing database will be destroyed)\n");
 (void)fprintf(stdout,"\t\t-p\tSpecify a priority for a new or updated entry\n");
 (void)fprintf(stdout,"\t\t-r\tRemove an entry from the database\n");
 (void)fprintf(stdout,"\t\t-T\tSet custom table name (should you want to interact with the database directly)\n");
 (void)fprintf(stdout,"\t\t-u\tUpdate a given entry\n");
 (void)fprintf(stdout,"\t\t-h\tThis text\n");
 (void)fprintf(stdout,"\tExample:\n\t\t%s -a -e\n",__progname);
}

int
db_reinit(const char *dbname) {
	/* kill and rebuild the task database */
	db_destroy(dbname);
	db_init(dbname);
	db_create_tables(dbname);
	return(0);
}

int
db_init(const char *dbname) {
	/* create the task database */
	int ret; /* check for return codes */
	(void)fprintf(stdout,"This is where we initialise task database: %s\n",dbname);
	do {
		/* start the engine */
		if ((ret = sqlite3_initialize()) != 0) {
			(void)fprintf(stderr,"Failed to initialize sqlite3 lib, ret:%d\n",ret);
			break;
		}
		(void)fprintf(stdout,"Task database at %s has been sucessfully created.\n", dbname);
		/* open a db connection */
		if ((ret = sqlite3_open(dbname, &taskdb)) != 0) {
			(void)fprintf(stderr,"Failed to open a connection to %s, ret:%d\n",dbname,ret);
			break;
		}
		sqlite3_close(taskdb);
	} while (1 < 0);
	return(0);
}

int
db_create_tables(const char *dbname) {
	/*
	 * Extra sqlite variables needed
	 */
	sqlite3_stmt* table_code = NULL;
	int ret; /* track the sqlite3 return values */ 
	const char *table_tail = '\0';
	/* TODO: this needs to be changed to work with any arbitrary table name */
	char *table_statement = "create table tasklist(id integer, title text, description text, priority integer, urgent integer, expires text, expired integer)";

	if ((sqlite3_open(dbname, &taskdb)) != 0) {
		fprintf(stderr,"ERR: Could not connect to database \"%s\"\n",dbname);
		return(1);
	} else {
		ret = sqlite3_prepare_v2(taskdb, table_statement, 1024, &table_code, &table_tail);
		if (ret != 0) { /* return  code is not "ok" or "done" */
			fprintf(stderr,"ERROR: %d\n",ret);
		} else {
			ret = sqlite3_step(table_code);
			if ((ret != 0) && (ret != 101)) {
				fprintf(stderr,"ERROR: %d\n",ret);
			}
		}
	}
	sqlite3_close(taskdb);
	return(0);
}

int
db_destroy(const char *dbname) {
	/* destroy the database */
	/* this should ALWAYS be interactive */
	char confirm;
	int ret;

	confirm = '\0'; /* NULL initialization */
	ret=0;

	/* verify that we want to actually delete the database */
	fprintf(stdout,"WARNING: This WILL delete all data in %s!\nAre you sure you want to continue? [y/N] ",dbname);
	scanf("%c",&confirm);
	fpurge(stdin);
	
	if (upperc(confirm) != 'N') {
		if (unlink(dbname) == 0) {
			fprintf(stdout,"Successfully deleted database %s\n",dbname);
			ret = 0;
		} else {
			(void)fprintf(stderr,"ERR: Could not delete %s!\n",dbname);
			ret = 2;
		}
	} else {
		fprintf(stdout,"Leaving %s alone...\n",dbname);
		ret =  0;
	}
	return(ret);
}

int
task_add_interactive(const char *dbname, const char *table_name) {
	/*
	 * This function should provide an interactive propmt 
	 * to add new entries to the task database. This function 
	 * should recturn the number of tasks added. 
	 */
	char retry;
	int ret, idx, expired, priority, added;
	sqlite3_stmt* table_code;
	const char *table_tail = NULL;
	char table_statement[2048];
	char  urgent;
	char *taskname, *taskdesc, *taskexpire;

	ret = sqlite3_open(dbname, &taskdb);
	retry = 'n';
	expired = idx = priority = added = 0;
	
	/* this should prevent incompatible pointer types from being used */
	if ((taskname = calloc(1, TASKSIZE)) == NULL) {
		fprintf(stderr,"Error allocating memory in task_add_interactive()\n");
		return(-1);
	}
	if ((taskdesc = calloc(1, DESCSIZE)) == NULL) {
		fprintf(stderr,"Error allocated memory in task_add_interactive()\n");
		return(-1);
	}
	if ((taskexpire = calloc(1, TASKEXPR)) == NULL) {
		fprintf(stderr,"Error allocating memory in task_add_interactive()\n");
		return(-1);
	}

	if (ret != 0) {
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
		} while ((taskdb == NULL) && (upperc(retry) != 'N'));
	}

	/* 
	 * Add tasks to the database as dictated by the user
	 */
	do {
		fprintf(stdout,"Enter the task name: ");
		getline(&taskname, &TASKSIZE, stdin);
		fprintf(stdout,"Enter the task description:\n");
		getline(&taskdesc, &DESCSIZE, stdin);
		fpurge(stdin);
		fprintf(stdout,"Enter the expiration date (YYYY-MM-DD): \n");
		getline(&taskexpire, &TASKEXPR, stdin);
		fpurge(stdin);
		fprintf(stdout,"Is this task urgent? [Y/n] ");
		urgent = fgetc(stdin);
		fpurge(stdin);
		fprintf(stdout,"What is the priority of this task? (1-10): ");
		fscanf(stdin,"%d",&priority);
		fpurge(stdin);

		expired = 0;
		/* This may need to be corrected to not contain newlines, or have them wrapped in quotes to work properly */
		snprintf(table_statement,(2 * DESCSIZE),"insert into %s (id, title, description, priority, urgent, expires, expired) values ('%d', '%s', '%s', '%d', '%c', '%s', '%d');",
		table_name, idx, taskname, taskdesc, priority, urgent, taskexpire, expired);
		fprintf(stdout,"\nUsed the following query:\n%s\n",table_statement);
		/* we should now have enough values to add data to the database */
		ret = sqlite3_prepare(taskdb, table_statement, 2048, &table_code, &table_tail);

		if (ret == 0) {
			ret = sqlite3_step(table_code);
			if ((ret == 0) || (ret == 101)) {
				fprintf(stdout,"Task %d sucessfully added.\nAdd another? [Y/n] ",idx);
				fscanf(stdin,"%c",&retry);
				fpurge(stdin);
				added++;
			} else {
				fprintf(stdout,"There was a problem adding that task: %d\nTry adding again? [Y/n] ",ret);
				fscanf(stdin,"%c",&retry);
				fpurge(stdin);
			}
		} else {
			fprintf(stdout,"There was a problem: %d\n",ret);
		}
		
		/*
		 * Zero out the variables for the next loop, 
		 * ensuring we don't end up with some garbage data
		 * being stored in the database.
		 */
		memset(&taskname, 0, (size_t)32);
		memset(&taskdesc, 0, (size_t)1024);
		memset(&taskexpire, 0, (size_t)10);
		urgent ^= urgent; 
		priority ^= priority;
	} while (upperc(retry) == 'Y');

	/* 
	 * Close the database connection if it exists 
	 */
	if (taskdb != NULL) {
		sqlite3_close(taskdb);
	}
	return(0);
}

int
db_check_expirations(const char *dbname) {
	/*
	 * Return the number of expired tasks
	 *
	 * This is essentially running through the 
	 * database, and checking the expirations against
	 * date('now');
	 */
	sqlite3_stmt* expire_statement;

	expire_statement = NULL;
	return(0);
}

int
task_list(int limit, const char *dbname) {
	/*
	 * List a set number of entries
	 * This function should be called directly from the command-line, 
	 * so we need to create a database handler.
	 */
	sqlite3_stmt* list_statement;

	list_statement = NULL;
	return(0);
}

void
pretty_print(char *sqlite_return) {
	/*
	 * format the returned entries to look nicer
	 */
}

long int
db_get_top(const char *dbname) {
	/*
	 * Get the current highest task number
	 * This function should run before any function 
	 * that actually modifies the database.
	 */
	sqlite3* taskdb;
	sqlite3_stmt* table_code;
	char *table_statement, *table_name; 
	long int ret;

	table_code = NULL;
	table_statement = NULL;
	ret = 0;

	if ((ret = sqlite3_open(dbname,&taskdb)) == NULL) {
		/* No database handler, bail out */
		fprintf(stderr,"Couldn't allocate space in db_get_top()\n");
	} 

	if ((ret = calloc((size_t)1024, (size_t)1)) == NULL) {
		fprintf(stderr,"Couldn't allocate space in db_get_top()\n");
	}
	 
	/* this may need to be replaced with an snprintf() call */
	/* strncat(&table_statement, "select max(id) from %s;", &table_name,  1023); */
	snprintf(table_statement, 1024, "select max(id) from %s;", &table_name);

	if (sqlite3_prepare(taskdb, table_statement, 1024, &table_code, NULL) != NULL) {
		ret = sqlite3_step(table_code);
	}

	if (ret == 0 || ret == 101) {
		/* hopefully this means that we have a sqlite3 blob we can work with */
		return(0);
	}


	return(0);
}

int 
db_reorder(const char *dbname) {
	/* 
	 * This function needs to adjust the values of any entries impacted by a deletion
	 * essentially the same idea as when you delete a line from the middle of the file
	 * shift all following lines down by one in the index per entry that's been deleted
	 */
	long int current_top; /* current top index value */
	long int new_top;

	current_top = new_top = 0;

	current_top = db_get_top(dbname);
	new_top = db_get_top(dbname);
	return(new_top);
}

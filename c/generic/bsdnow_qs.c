/*
 * Semi-serious BSDNow questions sources file,
 * To ask a few questions of Benedict and Allan.
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *__progname;

/* assign questions */
extern const char *allan_questions[10] = { "If you could no longer use UNIX-like systems, what OS would you use?\n", /* 1 */
																			"What part of the FreeBSD OS are you most fascinated with?\n",
																			"What is your favorite programming language?\n",
																			"What is the worst advice you\'ve ever recieved?\n",
																			"Which project are you most interested in at this time?\n", /* 5 */ 
																			"How do you feel about systemd being nominated for a pwnie?\n",
																			"How do you feel about the possibility of migrating to another init system like OpenRC or Runit?\n",
																			"If ZFS were no longer being developed, in some sort of dystopian future, which filesystem would you most likely use instead?\n",
																			"Do you run rootless Xorg, or do you not consider the security problems to be serious enough to worry about in daily use?\n",
																			"On the same note, how interested in Wayland adoption on BSD are you?\n"};

extern const char *benedict_questions[10] = { "If you could no longer use UNIX-like systems, what OS would you use?\n", /* 1 */
																				"What part of the FreeBSD OS are you most fascinated with?\n",
																				"What is the worst advice you\'ve ever recieved?\n",
																				"What is your favorite text editor?\n",
																				"What is your favorite programming language?\n", /* 5 */
																				"Which concepts do you find your students struggling with the most?\n",
																				"Does it bother you that Nvidia doesn't release any open source drivers like AMD and intel?\n",
																				"If you could get one change pushed and committed to FreeBSD by sheer force of will, what would it be?\n",
																				"What would your dream rig be?\n",
																				"What is your least favorite programming language?\n"};

/* ask questions for given host */
void ask_questions(char *name);
void cook_args(char *argv[]);
void cook_buf(FILE *);
/* dump the questions to a file instead */
void dump_questions(char *dumpname); 
void print_help(void);
void raw_args(char *argv[]);
int restart(char *again);
char * upper(char *s);

int
main(int argc, char *argv[]) { 
	char *name;
	char filename[1024];
	size_t namesize;
	short int totop,ch;
	unsigned short int dflag, fflag, hflag, aflag, bflag;

	namesize = 64;
	/* actually need space to hold the name of a host */
	if ((name = malloc(sizeof(char) * 64)) == NULL) { 
		(void)fprintf(stderr,"Could not allocate space for input buffer\n");
		return -2;
	}

	dflag = fflag = hflag = aflag = bflag = 0;
	while ((ch = getopt(argc, argv, "abdhf:")) != -1 ) {
		switch (ch){
			case 'a':
				aflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'd':
				dflag = 1;
				break;
			case 'f':
				fflag = 1;
				strncpy(filename,optarg,sizeof(filename));
				break;
			case 'h':
				print_help();
				return 0;
			default:
			/* if no flag is specified, run interactively */
				break;
		}
	}

	if (dflag == 1) {
		if (fflag == 1) {
			dump_questions(filename);
			return 0;
		}
		else {
			strncpy(filename,"questions.txt",sizeof(filename));
			dump_questions(filename);
			return 0;
		}
	}

	if (aflag == 1) {
		ask_questions("ALLAN");
		return 0;
	}
	if (bflag == 1) {
		ask_questions("BENEDICT");
		return 0;
	}

	/* No flags used, run interactively */
	do {
		/* here's where the questions go */
		(void)fprintf(stdout,"Please enter the host's name [ Allan/Benedict ]: ");
		getline(&name,&namesize,stdin);
		name = upper(name);
		
		if (name[0] == 0)
			return 0;

		ask_questions(name);
		bzero(name,64);

		/* ask if we want to exit */
		(void)fprintf(stdout,"Would you like to run through the interview again? [ y/N ]: ");
		getline(&name,&namesize,stdin);
		totop = restart(name);
		bzero(name,64);
	} while (totop != 0);
	free(name);
	return 0;
}

void
ask_questions(char *name) {
	int q;
	
	/* run through the questions for the given host */
	if (name[0] == 'A') {
		for (q = 0; q < 10; q++) {
			fprintf(stdout,"%s",allan_questions[q]);
			getchar();
		}
	}
	else if (name[0] == 'B') { 
		for (q = 0; q < 10; q++) { 
			fprintf(stdout,"%s",benedict_questions[q]);
			getchar();
		}
	}
}

void
dump_questions(char *dumpname) { 
	int q;
	FILE *filename;
	
	filename = fopen(dumpname, "a");
	if (filename == NULL ) { 
		fprintf(stderr,"Could not open %s for writing.\n",dumpname);
		abort();
	}

	/* this should dump all the questions to a file and tell the user where it is */
	(void)fprintf(filename,"Allan:\n");
	for (q = 0; q < 10; q++) { 
		(void)fprintf(filename, "%s",allan_questions[q]);
	}
	fflush(filename);

	(void)fprintf(filename,"\nBenedict:\n");
	for (q = 0; q < 10; q++) { 
		fprintf(filename, "%s",benedict_questions[q]);
	}
	fflush(filename);
	fclose(filename);
}

void
print_help(void) { 
	(void)fprintf(stdout,"Usage: %s [-abdhf]\n",__progname);
	(void)fprintf(stdout,"\t-a\tRun through Allan's questions\n");
	(void)fprintf(stdout,"\t-b\tRun through Benedict's questions\n");
	(void)fprintf(stdout,"\t-d\tDump questions to a file, defaults to \"questions.txt\"\n");
	(void)fprintf(stdout,"\t-f\tIn conjunction with \'-d\', specifies a new filename\n");
	(void)fprintf(stdout,"\t-h\tPrint this message\n");
}

int
restart(char *again) {
	/* simply determine if the user wants to go through another iteration */
	int index = 0;
	for (index = 0; again[index] != 0; index++) { 
	/* this could certainly be done better, but it's meant to be simple */
		if (again[index] == 'y' || again[index] == 'Y') { 
			return 1 ;
		}
		else
			return 0 ;
	}
}

char *
upper(char *s) {
	int index;
	int diff;

	diff = 97 - 65; /* difference between 'a' and 'A' */

	for (index = 0; s[index] != 0; index++) { 
		s[index] = (s[index] <= 'z' && s[index] >= 'a') ? (s[index] - diff) : s[index];
	}
	return s;
}

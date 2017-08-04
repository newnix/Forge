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
extern const char *allan_questions[10] = { "If you could no longer use UNIX-like systems, what OS would you use?\n",
																			"What part of the FreeBSD OS are you most fascinated with?\n",
																			"What is your favorite programming language?\n",
																			"What is the worst advice you\'ve ever recieved?\n",
																			"\n" };

extern const char *benedict_questions[10] = { "If you could no longer use UNIX-like systems, what OS would you use?\n",
																				"What part of the FreeBSD OS are you most fascinated with?\n",
																				"What is the worst advice you\'ve ever recieved?\n",
																				"What is your favorite text editor?\n",
																				"What is your favorite programming language?\n" };

/* ask questions for given host */
void ask_questions(char *name);
void cook_args(char *argv[]);
void cook_buf(FILE *);
/* dump the questions to a file instead */
void dump_questions(void, const char *dumpname); 
void raw_args(char *argv[]);
int restart(char *again);
void upper(char *s);

int
main(int argc, char *argv[]) { 
	char *again;
	char *name;
	short int totop,ch;
	unsigned short int dflag, fflag, hflag, aflag, bflag;

	dflag = fflag = hflag = aflag = bflag = 0;
	while ((ch = getopt(argc, argv, "abdhf:")) != -1 ) {
		switch ch {
			case 'a':
				break;
			case 'b':
				break;
			case 'c':
				break;
			case 'f':
				break;
			case 'h':
				return 0;
			default:
				return 0;
		}
	}

	do {
		/* here's where the questions go */
		printf("Please enter the host's name [ Allan/Benedict ]: ");
		scanf("%[^\n]",*name);
		upper(name);
		ask_questions(name);

		/* ask if we want to exit */
		printf("Would you like to run through the interview again? [ y/N ]: ");
		scanf("%[^\n]",*again);
		totop = restart(again);
	} while (totop != 0);
	return 0;
}

void
ask_questions(char *name) {
	int q;
	char *cont; /* just hold a  character */
	
	if ((cont = malloc(sizeof(char))) == NULL) { 
		fprintf(stderr,"Could not allocate buffer\n");
	}
	else {
		/* run through the questions for the given host */
		if (name == "ALLAN") {
			for (q = 0; q < 5; q++) {
				fprintf(stdout,"%s",*allan_questions[q]);
				scanf("%[^\n]",cont);
			}
		}
		else if (name == "BENEDICT") { 
			for (q = 0; q < 5; q++) { 
				fprintf(stdout,"%s",*benedict_questions[q]);
				scanf("%[^\n]",cont);
			}
		}
	}
}

void
dump_questions(void, const char *dumpname) { 
	int q;
	FILE *filename;
	
	filename = fopen(dumpname, "a");
	if (filename == NULL ) { 
		fprintf(stderr,"Could not open questions.txt for writing.\n");
	}

	/* this should dump all the questions to a file and tell the user where it is */
	for (q = 0; q < 5; q++) { 
		fprintf(filename, "%s\n",*allan_questions[q]);
	}
	fflush(filename);

	for (q = 0; q < 5; q++) { 
		fprintf(filename, "%s\n",*benedict_questions[q]);
	}
	fflush(filename);
	fclose(filename);
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

void
upper(char *s) {
	int index;
	int diff;

	index = 97 - 65; /* difference between 'a' and 'A' */

	for (index = 0; s[index] != 0; index++) { 
		s[index] = (s[index] <= 'z' && s[index] >= 'a') ? (s[index] - diff) : s[index];
	}
}

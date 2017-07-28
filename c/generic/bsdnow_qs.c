/*
 * Semi-serious BSDNow questions sources file,
 * To ask a few questions of Benedict and Allan.
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <ctype.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *__progname;

/* ask questions for given host */
void ask_questions(char *name);
void cook_args(char *argv[]);
void cook_buf(FILE *);
/* dump the questions to a file instead */
void dump_questions(void); 
void raw_args(char *argv[]);
int restart(char *again);
void upper(char *s);

int
main(int argc, char *argv[]) { 
	char **allan_questions;
	char **benedict_questions;
	char *again;
	char *name;
	int totop;

	do {
		/* here's where the questions go */
		printf("Please enter the host's name [ Allan/Benedict ]: ");
		scanf("%[^\n]",*name);
		ask_questions(*name);

		/* ask if we want to exit */
		printf("Would you like to run through the interview again? [ y/N ]: ");
		scanf("%[^\n]",*again);
		totop = restart(*again);
	} while (totop != 0);
	return 0;
}

void
ask_questions(char *name){
	int q;

	/* run through the questions for the given host */
	switch (upper(*name)) {
		case "ALLAN":
			for (q = 0; q < numqustions; q++) { 
				printf("%s\n",*allan_questions[q]);
			}
			break;
		case "BENEDICT":
			for (q = 0; q < numquestions; q++) { 
				printf("%s\n",*benedict_questions[q]);
			}
			break;
		default:
			dump_questions();
			break;
	}
}

void
dump_questions(void) { 
	int q;
	FILE *filename = fopen("questions.txt", "a");
	if (filename == NULL ) { 
		err("%s", *filename);
	}

	/* this should dump all the questions to a file and tell the user where it is */
	for (q = 0; q < numquestions; q++) { 
		fprintf(*filename, "%s\n",*allan_questions[q]);
	}
	fflush(*filename);

	for (q = 0; q < numquestions; q++) { 
		fprintf(*filename, "%s\n",*benedict_questions[q]);
	}
	fflush(*filename);

	fclose(*filename);
}

int
restart(char *again) {
	/* simply determine if the user wants to go through another iteration */
	int index = 0;
	for (index = 0; again[index] != 0; index++) { 
	/* this could certainly be done better, but it's meant to be simple */
		(again[index] == 'y' || again[index] == 'Y') ? return 1 : return 0 ;
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

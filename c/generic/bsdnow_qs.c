/*
 * Semi-serious BSDNow questions sources file,
 * To ask a few questions of Benedict and Allan.
 */

#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <ctype.h>

/* ask questions for given host */
void ask_questions(char *name);
/* dump the questions to stdout instead */
void dump_questions(void); 

int
main(int argc, char *argv[]) { 
	char **allan_questions;
	char **benedict_questions;
	/* here's where the questions go */
	return 0;
}

void
ask_questions(char *name){
	/* run through the questions for the given host */
	switch upper(*name) {
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
			break;
	}
}

void
dump_questions(void) { 
	int q;
	for (q = 0; q < numquestions; q++) { 
		printf("%s\n",*allan_questions[q]);
	}
	for (q = 0; q < numquestions; q++) { 
		printf("%s\n",*benedict_questions[q]);
	}
}

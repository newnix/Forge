/* 
 * this is meant to be a simple implementation of a doubly-linked list
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct node {
	uint16_t *previous;
	uint16_t *next;
	uint8_t id;
	char name[9];
} node;

static int delnode(uint8_t id);
static int getnode(char *name);
static int mknode(char *name);
static void nodewalk(uint8_t id);
static int parse(char *input); /* return id if found, 0 if no id found but fine, -1 otherwise */
static void printnode(uint8_t id);

int 
main(void) { 
	/* need to do some magic here */
	char *line;
	ssize_t captured;
	size_t linecap;

	captured = 0;
	line = NULL;
	linecap = 1024;

	if ((line = calloc(1,linecap)) == NULL) { 
		fprintf(stderr,"Cannot get memory for input!\n");
		return(1);
	}
		
	fprintf(stdout,"Commands:\n\tcreate [id] [name]:\tcreates node with id and name\n\t"
	               "del [id]:\tdeletes node with id [id]\n\t"
								 "get [name]:\tshow node info for node with [name]\n\t"
								 "walk [id]:\tdisplay all nodes, starting from [id] (default 0)\n");
	fprintf(stdout,"Enter a command: ");
	while ((captured = getline(&line,&linecap,stdin)) > 0) { 
		/* should be a better way, but I'm not terribly interested in performance here */
		if (strnstr(line,"create",linecap) != NULL) { 
			parse(line);
			mknode(line);
		}
		else if (strnstr(line,"del",linecap) != NULL) { 
			delnode(parse(line));
		}
		else if (strnstr(line,"get",linecap) != NULL) {
			parse(line);
			getnode(line);
		}
		else if (strnstr(line,"walk",linecap) != NULL) {
			nodewalk(parse(line));
		}
		else { 
			fprintf(stdout,"Invalid command!\nExit? [N/y]\n");
		}
	}

	if (line != NULL) { 
		free(line);
	}
	return(0);
}

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
	char stop,*line;
	ssize_t captured;
	size_t linecap;

	stop = 'n';
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
	while (((stop & 0x5F) != 'Y') && ((captured = getline(&line,&linecap,stdin)) > 0)) { 
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
		} else if (strnstr(line,"help",linecap) != NULL) { 
		} 
		else { 
			fprintf(stdout,"Invalid command!\nExit? [N/y]\n");
			stop ^= stop;
			stop = getchar();
			/* 
			 * We're only concerned with values from 65-90
			 * 0100 0001 - A | 65 | 0x41
			 * 0101 1010 - Z | 90 | 0x5A
			 * 
			 * mask should most likely be 0101 1111
			 */
		}
	}

	if (line != NULL) { 
		free(line);
	}
	return(0);
}

static int
delnode(uint8_t id) { 
	return(0);
}

static int
getnode(char *name) { 
	return(0);
}

static int
mknode(char *name) { 
	static uint8_t id = 0;
	node *new;

	if ((new = calloc(1,sizeof(*new))) == NULL) {
		return(-1);
	}

	/* assign values to the node structure */
	new->id=id;
	id++;
	strlcpy(new->name,name,8);

	return(0);
}

static void
nodewalk(uint8_t id) { 
}

static int
parse(char *input) { 
	return(0);
}

static void
printnode(uint8_t id) { 
}

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
static void nodewalk(uint8_t id, uint8_t clean);
static int parse(char *input); /* return id if found, 0 if no id found but fine, -1 otherwise */
static void printnode(node *node);
extern uint16_t *origin = NULL;

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
		
	/* this string should be available to print on demand */
	fprintf(stdout,"Commands:\n\tcreate [id] [name]:\tcreates node with id and name\n\t"
	               "del [id]:\tdeletes node with id [id]\n\t"
								 "get [name]:\tshow node info for node with [name]\n\t"
								 "walk [id]:\tdisplay all nodes, starting from [id] (default 0)\n");
	fprintf(stdout,"Enter a command: ");
	while (((stop & 0x5F) != 'Y') && ((captured = getline(&line,&linecap,stdin)) > 0)) { 
		/* should be a better way, but I'm not terribly interested in performance here */
		if (strnstr(line,"create",linecap) != NULL) { 
			parse(line);
			if (mknode(line) == 0) { 
				fprintf(stderr,"%s->previous:\t%p\n%s->id:\t%u\n%s->name:\t%s\n%s->next:\t%p\n",line,line->previous,line,line->id,line,line->name,line,line->next);
			}
		}
		else if (strnstr(line,"del",linecap) != NULL) { 
			delnode(parse(line));
		}
		else if (strnstr(line,"get",linecap) != NULL) {
			parse(line);
			getnode(line);
		}
		else if (strnstr(line,"walk",linecap) != NULL) {
			nodewalk(parse(line),0);
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
		memset(line,0,linecap);
	}

	if (line != NULL) { 
		free(line);
	}
	nodewalk(0,1);
	return(0);
}

/* 
 * this should delete a node from the list 
 * and then update the pointers of its neighbors
 * should also be used to clean up before exiting.
 */
static int
delnode(uint8_t id) { 
	return(0);
}

/* 
 * This will print the node info for the 
 * node with a given name, else return -1
 */
static int
getnode(char *name) { 
	return(0);
}

/* 
 * This is the function that handles node creation 
 * and updating the node->next pointer of the previous node
 *
 * It may be necessary to tweak this such that it accepts a 
 * pointer to a node struct, as I'm unsure how exactly 
 * the best method is for keeping and tracking the items 
 * in the heap are
 */
static int
mknode(char *name) { 
	static uint8_t id = 0;
	node *new;

	if ((new = calloc(1,sizeof(*new))) == NULL) {
		return(-1);
	}
	if (origin != NULL) { 
		new->previous = NULL;
		new->next = &new;
		origin = &new;
	}

	/* assign values to the node structure */
	new->id=id;
	id++;
	strlcpy(new->name,name,8);

	return(0);
}

/*
 * This function simply walks the whole list 
 * until node->next == NULL, and passes the node 
 * to the node printing function
 */
static void
nodewalk(uint8_t id, uint8_t clean) { 
}

/*
 * This will simply take the command from the user
 * and hand off the name/id to the next function
 * by modifying the string and returning an id
 * if found, 0 otherwise, and -1 if an error is encountered
 */
static int
parse(char *input) { 
	return(0);
}

/* 
 * This function simply dumps the contents of the 
 * node struct for a given node to stdout
 */
static void
printnode(node *node) { 
}

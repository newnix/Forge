/* 
 * this is meant to be a simple implementation of a doubly-linked list
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINECAP 1024

typedef struct node {
	struct node *previous;
	struct node *next;
	uint8_t id;
	char name[9];
} node;

static int delnode(uint8_t id);
static int getnode(char *name);
static node * mknode(char *name);
static void nodewalk(uint8_t id, uint8_t clean);
static int parse(char *input); /* return id if found, 0 if no id found but fine, -1 otherwise */
static void printnode(node *node);
extern node *origin = NULL;

int 
main(void) { 
	/* need to do some magic here */
	char stop,*line;
	char *instructions = "Commands:\n\tcreate [name]:\tcreates node with id and name\n\tdel [id]:\tdeletes node with id [id]\n\tget [name]:\tshow node info for node with [name]\n\twalk [id]:\tdisplay all nodes, starting from [id] (default 0)\n";

	ssize_t captured;
	size_t linecap;
	node *curnode;

	stop = 'n';
	captured = 0;
	line = NULL;
	linecap = LINECAP;

	if ((line = calloc(1,LINECAP)) == NULL) { 
		fprintf(stderr,"Cannot get memory for input!\n");
		return(1);
	}
		
	/* this string should be available to print on demand */
	fprintf(stdout,"%s",instructions);
	fprintf(stdout,"Enter a command: ");
	while (((stop & 0x5F) != 'Y') && ((captured = getline(&line,&linecap,stdin)) > 0)) { 
		/* should be a better way, but I'm not terribly interested in performance here */
		if (strnstr(line,"create",LINECAP) != NULL) { 
			parse(line);
			if ((curnode = mknode(line)) != NULL) { 
				printnode(curnode);
			}
		}
		else if (strnstr(line,"del",LINECAP) != NULL) { 
			delnode(parse(line));
		}
		else if (strnstr(line,"get",LINECAP) != NULL) {
			parse(line);
			getnode(line);
		}
		else if (strnstr(line,"walk",LINECAP) != NULL) {
			nodewalk(parse(line),0);
		} else if (strnstr(line,"help",LINECAP) != NULL) { 
			fprintf(stdout,"%s",instructions);
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
		memset(line,0,LINECAP);
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
	node *node;

	node = origin;

	for (; node != NULL; node = node->previous) {
		if (strnstr(node->name, name, LINECAP) != NULL) {
			printnode(node);
			return(0);
		}
	}
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
static node *
mknode(char *name) { 
	static uint8_t id = 0;
	static node *new;

	if ((new = calloc(1,sizeof(*new))) == NULL) {
		return(NULL);
	}

	if (origin == NULL) { 
		new->previous = NULL;
		new->next = new;
	} else {
		new->previous = origin;
		new->previous->next = new;
		new->next = NULL;
	}
	origin = new;

	/* assign values to the node structure */
	new->id=id;
	id++;
	strlcpy(new->name,name,8);

	return(new);
}

/*
 * This function simply walks the whole list 
 * until node->next == NULL, and passes the node 
 * to the node printing function
 */
static void
nodewalk(uint8_t id, uint8_t clean) { 
	node *node;

	node = origin;

	if (clean == 0) {
		for (; node != NULL; node = node->previous) {
			fprintf(stdout,"Node info for node %d\n",node->id);
			printnode(node);
		}
	}
}

/*
 * This will simply take the command from the user
 * and hand off the name/id to the next function
 * by modifying the string and returning an id
 * if found, 0 otherwise, and -1 if an error is encountered
 */
static int
parse(char *input) { 
	int i, j, len, sep;
	i = j = len = sep = 0;

	len = strlen(input);

	for (i = 0; input[i] != ' '; i++) {
		;
	}

	/* this is the location of the first separator */
	sep = i;

	for (i++,j = 0; input[j] != 0; i++,j++) {
		/* this needs to convert the string to something like id\0name */
		input[j] = input[i]; /* start input[j] at the character after the first separator */
		if (input[i] == '\n') {
			do {
				input[j] = 0;
				j++;
			} while (j < len);
		}
	}
	return(0);
}

/* 
 * This function simply dumps the contents of the 
 * node struct for a given node to stdout
 */
static void
printnode(node *node) { 
	fprintf(stdout,"\nnode: %p\nname: %s\nid: %u\nprevious: %p\nnext: %p\n",node,node->name,node->id,node->previous,node->next);
}

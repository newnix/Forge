/* 
 * This is meant to re-implement the basic utility of
 * ls(1), to provide practice with directory traversal
 */

#include <err.h>
#include <errno.h>
#include <fts.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;
extern char *__progname;

int
main(int argc, char **argv) { 
	/* here we need to determine what sort of flags are going to be used */
	return(0);
}

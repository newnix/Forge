/* 
 * Basically just to practice file I/O
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *__progname;

/* dump self to file */
int dump_source(void);
/* dump self to stdout instead */
int print_source(void);

int
main(int argc, char *argv[]) { 
	
	int ch;
	unsigned short int dflag, hflag;

	while ((ch = getopt(argc, argv, "dh")) != -1 )
		switch (ch) { 
			case 'd':
				dflag = 1;
				break;
			case 'h':
				hflag = 1;
				(void)fprint(stderr, "usage: %s [-dh]\n",__progname);
				break;
			default:
				(void)fprint(stderr, "usage: %s [-dh]\n",__progname);
				return 1;
			}
		argv += optind;

		if (dflag)
			dump_source;
		else
			print_source;

		if (fclose(stdout))
			err(1, "stdout");
		return rval;
}

int
dump_source(void) {
	FILE *sources, *source2;
	char *filename = "fopen.c";
	char *filedump = "fopen.dup";
	
	sources = fopen(filename, "r");
	source2 = fopen(filedump, "a");

	while read(sources,line) {
		fprint(filedup,"%s\n",line);
	}
	if (fclose(sources) && fclose(source2)) { 
		return 0;
	}
	else
		return -1;
}

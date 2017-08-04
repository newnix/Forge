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
int print_sources(void);

int
main(int argc, char *argv[]) { 
	
	int ch;
	unsigned short int dflag, hflag;

	dflag = hflag = 0;

	while ((ch = getopt(argc, argv, "dh")) != -1 )
		switch (ch) { 
			case 'd':
				dflag = 1;
				break;
			case 'h':
				hflag = 1;
				(void)fprintf(stderr, "usage: %s [-dh]\n",__progname);
				return 0;
			default:
				(void)fprintf(stderr, "usage: %s [-dh]\n",__progname);
				return 0;
	}
	argv += optind;

	if (dflag == 1)
		return (int)dump_source();
	else
		return (int)print_sources();
}

int
dump_source(void) {
	FILE *sources, *source2;
	char *filename = "fopen.c";
	char *filedump = "fopen.dup";
	char *filechunk; /* hold a bit of the file */
	
	sources = fopen(filename, "r");
	source2 = fopen(filedump, "a");

	if ( sources != NULL && source2 != NULL ) { 
		if ((filechunk = malloc(sizeof(char) * 32)) != NULL) {
			while (fread(filechunk, sizeof(char), 32, sources)) {
				fwrite(filechunk, sizeof(char), 32, source2);
				bzero(filechunk,32);
			}
		}
		if (fclose(sources) && fclose(source2)) { 
			return 0;
		}
		else
			return -1;
	}
	else
		return -1;
}

int
print_sources(void) { 
	FILE *sources;
	char *filename = "fopen.c";
	char *filechunk;

	sources = fopen(filename, "r");

	if ( sources != NULL ) { 
		if ((filechunk = malloc(sizeof(char) * 32)) != NULL) {
			while (fread(filechunk, sizeof(char), 32, sources)) { 
				(void)fprintf(stdout, "%s", filechunk);
					bzero(filechunk,32);
			}
		}
		fclose(sources);
	}
	else
		return -1;
}
		

/* Copyright (c) 2017-2018, Exile Heavy Industries
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without specific
 *   prior written permission.
 * 
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
 * LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/* for wait() */
#include <sys/types.h>
#include <sys/wait.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* literal ASCII null/newline */
#define SEP_IS_NULL 0
#define SEP_IS_NEWL 10
#define ARGV_MAX 1024

extern char **environ;
extern char *__progname;

static int abandon_env(void);
static void nxenv(char envsep);
static void run_help(void);

int
main(int argc, char **argv) {
	int ch, i, j, ret;
	char **cargv;
	char envsep;
	char *envp;
	pid_t child;

	child = 0;
	ch = i = j = 0;
	envsep = SEP_IS_NEWL;

	if ((cargv = calloc(ARGV_MAX, ARGV_MAX)) == NULL) {
		err(errno, "calloc: ");
	} 

	while ((ch = getopt(argc, argv, "hi0")) != -1) {
		switch(ch) {
			case 'h':
				run_help();
				return(0);
			case 'i': 
				abandon_env();
				break;
			case '0':
				envsep = SEP_IS_NULL;
				break;
			default:
				break;
		}
	}
	/* 
	 * need to convert this to use optind to determine where options end
	 * Ideally also move to a separate function
	 */
	for (ch = optind; ch < argc; ch++) {
		/* we have a new env var, add it to **environ */
		if ((envp = strchr(argv[ch],'=')) != NULL) { 
			if ((ret = putenv(argv[ch])) != 0) { 
				err(ret, "putenv: "); /* this is almost certainly wrong, needs revisitng */
			}
		} else {
			strlcpy(cargv[i], argv[ch], ARGV_MAX);
			if (i == 0) { j = ch; }
			err(errno, "strlcpy: ");
			i++;
		}
	}
	if (i > 0) {
		child = fork(); 
		if (child > 0) { 
			/* in the parent process */
			wait(&child);
		} else {
			/* child process */
			execve(argv[j], cargv, environ);
		}
	}
	if (j == 0) { 
		nxenv(envsep);
	}
	free(cargv);
	return(0);
}

static int
abandon_env(void) {
	/* 
	 * going to need to clear **environ, then fork() & execve() the given command
	 */
	memset(environ, 0, sizeof(*environ));
	/* scan_args(**argv); */
	return(0);
}

static void
nxenv(char envsep) {
	for(int i = 0; environ[i] != NULL; i++) {
		fprintf(stdout,"%s%c",environ[i],envsep);
	}
}

static void
run_help(void) {
	fprintf(stdout,"%s: New Exile's env(1)\n",__progname);
	fprintf(stdout,"\t-h\tThis help text\n");
	fprintf(stdout,"\t-i\tDiscard the environment for a new process\n");
	fprintf(stdout,"\t-0\tUse NULL for separation, instead of newline\n");
}

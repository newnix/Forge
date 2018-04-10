#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char **environ;

int
main(void) {
	pid_t child;
	child = 0;

	fprintf(stdout,"Current PID: %d\n",getpid());
	char *args[4] = {  "/bin/sh", "-c", "/home/newnix/bin/c/nxenv" ,  0  };

	if ((child = fork()) != 0) {
		fprintf(stdout,"Current PID: %d\n",getpid());
		execve("/bin/sh",args, environ);
	} else if (child == -1) {
		fprintf(stderr,"Could not create child process!\n");
	}
	return(0);
}

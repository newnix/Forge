/* 
 * this is more example code from https://en.wikipedia.org/wiki/Callback_(computer_programming)
 * this example is meant to demonstrate using callbacks as a means to pass messages 
 * without having to expose potentially sensitive information
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct _Msg {
	int appID;
	char body[32];
} Msg;

void
myfunc(Msg *msg) {
	if (strlen(msg->body) > 0) { 
		printf("AppID = %d\tMsg = %s\n", msg->appID, msg->body);
	} else { 
		printf("AppID = %d\tHas Nothing to Say\n", msg->appID);
	}
}

/* prototype decl */
void (*callback)(Msg *);

int
main(void) { 
	Msg msg1;
	msg1.appID = getpid();
	strcpy(msg1.body, "Testing\n");

	/* 
	 * assing the address of the function "myfunc" to the function pointer "callback"
	 */
	callback = myfunc;
	
	callback(&msg1);
	return(0);
}

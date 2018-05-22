/* 
 * nxt, by Newnix of Exile Heavy Industries
 * meant to be a simple terminal emulator, similar 
 * to st from suckless, but with video acceleration.
 *
 * This way it's possible to watch videos inside the terminal
 * or at least get some extra functionality/eye candy available.
 */

/*
 * st has several other files included, I'm not sure why this is yet
 * this is the bare minimum that should be necessary to get a semifunctional 
 * terminal emulator working
 */
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <wchar.h>

#include "config.h"

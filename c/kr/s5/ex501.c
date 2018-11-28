/* 
 * Getint with signs 
 * Create a function, getint() that will push the values +/- 
 * not followed by an integer, back instead of treating them as 0
 */

static int kr_isdigit(char *x);

static int
kr_isdigit(char *x) {
	if ((*x >= 48) && (*x <= 57)) {
		return(1);
	} else {
		return(0);
	}
}

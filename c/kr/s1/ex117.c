/* exercise 1-17 from K&R's ANSI C 
 * meant to print any lines from stdin
 * that are greater than 80 chars long
 */

/* pseudocode for this objective:
 * if (there's a line from stdin)
 * {
 * 	determine the length;
 * 	if (length > 80)
 * 	{
 * 		print line;
 * 	}
 * 	else if (length > 0)
 * 	{
 * 		reset the counter(s);
 * 	}
 * 	else
 * 	{
 * 		terminate;
 * 	}
 * }
 */

#include <stdio.h>
#define MIN 80 /* the minimum size to print */
#define MAX 1000 /* max input size I'm willing to allow */

/* forward declarations, functions will be defined later */
int get_line(char s[], int lim); /* again using get_line instead of getline */
void copy(char to[], char from[]); /* copy one char array into another */

int main()
{
	/* declare the vars needed, such as the char arrays to be tested/saved */
	int len, str; /* current length */
	char curstr[MAX], printstr[MAX]; /* char arrays for the string comparisons */

}

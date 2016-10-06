/* Exercise 1-18 from K&R's ANSI C
 * meant to delete runs of blank chars
 */

#include <stdio.h>
#define MAX 1000 /* I don't want to deal with your crazy strings */

/* forward declarations */
int get_line(char s[], int lim); /* get a line from stdin */
char[] condense(char s[], int a, int b, int c); /* condense whitespace */
void copy(to[], from[]); /* copy one string into another */

int main()
{
	/* declare main vars */
	char curstr[], printstr[]; /* char arrays for the copy function */
	int len; /* count the length of a string of input */

	while ((len = get_line(curstr, MAX)) > 0 )
	{
		copy(condense(curstr), printstr);
		printf("%s", printstr);
	}
	/* program ends if it reaches EOF or len == 0 */
	return 0;
}

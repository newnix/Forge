/* copy stdin to stdout */
#include <stdio.h>

/* rev3 */
/* this version is meant to display how removing a set of parens creates a value assignment to 'c' */

main()
{
	int c;

	while ( c = getchar() != EOF )
	{
		printf("%d\n",c);
	}
}

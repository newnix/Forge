/* count the chars in stdin */
#include <stdio.h>

/* rev1 */
main()
{
	long nc; /* number of chars */

	nc = 0;
	while (getchar() != EOF)
	{
		++nc; /* increment charcount by one */
	}
	/* use 'ld' not '1d', this is set as a long int */
	printf("%ld\n",nc);
}

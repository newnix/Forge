/* copy stdin to stdout */
#include <stdio.h>

/* rev2 */
main()
{
	int c;

	while ((c = getchar()) != EOF)
		putchar(c);
}

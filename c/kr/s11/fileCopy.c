/* copy stdout to stdin */
#include <stdio.h>

/* rev1 */
main()
{
	int c;

	c = getchar();
	/* while 'c' is not End Of File (^D) */
	while (c != EOF)
	{
		putchar(c);
		c = getchar();
	}
}

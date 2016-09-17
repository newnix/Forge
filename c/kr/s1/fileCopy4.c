/* copying stdin to stdout */
#include <stdio.h>

/* this version is meant to print the EOF value */
main()
{
	int c;

	while ( (c = getchar()) == EOF )
	{
		printf("int val: %d\nchar val: %c",c,c);
	}
}

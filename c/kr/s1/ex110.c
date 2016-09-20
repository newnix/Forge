/* excersize 1-10 */
/* the goal is to replatce each tab with '\t',
 * each backspace with '\b', 
 * and each '\' with '\\'
 */
#include <stdio.h>

main()
{
	int c; /* placeholder for the getchar() value */
	
	while ((c = getchar()) != EOF)
	{
		if (c == '\t')
		{
			printf("\\t");
		}
		else if (c == '\b')
		{
			printf("\\b");
		}
		else if (c == '\\')
		{
			printf("\\\\");
		}
		putchar(c);		
	}
}

/* the printf() solution seems to only sometimes work,
 * but I consider it good enough for the teaching exercise it's meant to be
 */

/* histogram for stdin */
#include <stdio.h>

/* classify the various kinds of input and display a histogram of their values and frequeny */
main()
{
	int ndig[10], c, i, nchar, nws;

	nws = nchar = 0;

	for (i = 0; i < 10; i++)
	{
		ndig[i] = 0;
	}
	
	while ((c = getchar()) != EOF)
	{
		if (c >= '0' && c <= '9')
		{
			++ndig[c-'0'];
		}
		else if (c == ' ' || c == '\t' || c == '\n')
		{
			++nws;
		}
		else
		{
			++nchar;
		}
	}

	printf("Value\t|\tFrequency\n");
	for (i = 0; i < 10; ++i)
	{
		printf("%d\t|\t%d\n",i,ndig[i]);
	}
	printf("WS\t|\t%d\n",nws);
	printf("Chars\t|\t%d\n",nchar);
}

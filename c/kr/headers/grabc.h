#ifndef _GRABC_H_
#define _GRABC_H_

char grabc()
{
	/* get me a char! */
	int i, c;
	while ((i = getchar()) != EOF && i != '\n' && i != 0)
	{
		c = i; /* this will take the last char given that is not NULL or a newline */
	}
	return c;
}

#endif

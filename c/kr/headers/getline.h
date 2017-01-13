#ifndef GETLINE_H
#define GETLINE_H

int getline(char s[], int max)
{
	int c, i; /* used to step through a C string */

	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
	{
		s[i] = c;
	}
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

#endif

#ifndef GETLINE_H
#define GETLINE_H

/* this is the method used in exgrep.c, from section 4 */
int get_line(char *s, int lim) {
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') { 
		s[i++] = c;
	}
	if (c == '\n')
		s[i++] = c;
	s[i] = 0;

	return i;
}
/* Replacing with revised function found in later exercise
int get_line(char s[], int max)
{
	int c, i;

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
*/
#endif

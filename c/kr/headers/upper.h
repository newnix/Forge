#ifndef CHARCONV_H
#define CHARCONV_H

/* convert characters to uppercase */
/* this version only works on one char at a time */
char upperc(char c)
{
	int upperdiff; /* difference between 'a' and 'A' */
	upperdiff = (97 - 65);
	/* checks if the value is between 'z' and 'a', then adjust if needed */
	c = ((c <= 'z') && (c >= 'a')) ? (c - upperdiff) : c;
	return c;
}

/* converts all chars in a string to uppercase */
void upper(char s[])
{
	int i;
	int upperdiff;
	upperdiff = (97 - 65);

	for (i = 0; s[i] != 0; i++)
	{
		/* turns out ternary is pretty simple and fun */
		s[i] = ((s[i] >= 'a') && (s[i] <= 'z')) ? (s[i] - upperdiff) : s[i];
	}
}

/* converts all chars in a string to lowercase */
void lower(char s[])
{
	int i;
	int upperdiff;
	upperdiff = (97 - 65);

	for (i = 0; s[i] != 0; i++)
	{
		s[i] = ((s[i] >= 'A') && (s[i] <= 'Z')) ? (s[i] + upperdiff) : s[i];
	}
}

/* convert a single char to lowercase */
char lowerc(char c)
{
	int upperdiff;
	upperdiff = (97 - 65);

	c = ((c <= 'Z') && (c >= 'A')) ? (c + upperdiff) : c;
	return c;
}
#endif

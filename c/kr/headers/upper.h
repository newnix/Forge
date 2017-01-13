#ifndef UPPER_H
#define UPPER_H

char upper(int c)
{
	int upperdiff; /* difference between 'A' and 'a' */
	upperdiff = (97 - 65);

	if ((c <= 122) && (c >= 97)) /* between 'z' and 'a' */
		c = (c - upperdiff);
	
	return c;
}

#endif

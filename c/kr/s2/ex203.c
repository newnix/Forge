/* 
 * Exercise 2-3 on page 46 of K&R
 * get a string of input from the user,
 * then convert it from hex to an integer
 */

#define max 20 /* because wtf are you thinking if you give me more than that in hex?? */

#include <stdio.h>
#include <math.h>

/* htoi() -> hex to int */
/* This should return an int from a given string */
double htoi(char s[], int len);
int get_line(char s[], int lim);
double hexcon(char h[], int len); /* essentially a switch statement with hex values */
char upper(int c); /* convert lower char to upper */

int main()
{
	char hexin[max]; /* string containing the hex value */
	int len;
	
	printf("Enter a hexadecimal value, with or without the leading \"0x\":\n");
	
	while ((len = get_line(hexin, max)) > 0)
	{
		/* not sure what to put here yet */
		printf("%s\n",hexin);
		printf("Is %.0f when converted to an integer.\n",htoi(hexin,len));
	}

	return 0;
}

int get_line(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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

double htoi(char s[], int len)
{
	/* will have to check the string for valid hex values */
	int i; /* used to step through the string, checking for invalid values */
	int h; /* holds the value of hex[] so we have a valid hex string */
	char hex[max]; /* verified hex string */
	int hlen; /* separate the length of the string from the conversion string */
	
	h = 0;
	/* switch for the possibility of a preceeding '0x' */
	if ((s[0] == '0') && (upper(s[1]) == 'X'))
	{
		hlen = len - 2;
		/* start i at 2 */
		for (i = 2; i < max - 1; i++)
		{
			/* test for the int values for various valid characters */
			if ((upper(s[i]) >= 'A' && upper(s[i]) <= 'F') || (s[i] >= 48 && s[i] <= 57))
			{
				/* collect the values so we can turn them into an int later */
				hex[h] = s[i]; 
				h++;
			}
		} hex[h + 1] = '\0';
	}
	else
	{
		hlen = len;
			/* start i at 0 */
		for (i = 0; i < max - 1; i++)
		{
			/* test for the int values for various valid characters */
			if ((upper(s[i]) >= 'A' && upper(s[i]) <= 'F') || (s[i] >= 48 && s[i] <= 57))
			{
				/* collect the values so we can turn them into an int later */
				hex[h] = s[i];
				h++;
			}
		} hex[h + 1] = '\0';
	/* after verifying it's good, convert to an integer value */
	}
	return hexcon(hex,hlen);
}

/*
 * The general formula for converting a hex value to an int is (<value> x 16^n-1)+(<value-1> x 16^n-2)
 * and so on. The values range from 0-15 (int) and 0-9,A-F (hex).
 * With the current setup, the power limit's 99, this is likely going to be excessive.
 * I think I'll lower it to something more sensible like 20.
 */
double hexcon(char h[], int len)
{
	/* here we convert things to an int */
	/* This will simply hold the decimal values of the hex characters */
	/*
	 * 0 = 0    8 = 8
	 * 1 = 1    9 = 9
	 * 2 = 2    A = 10
	 * 3 = 3    B = 11
	 * 4 = 4    C = 12
	 * 5 = 5    D = 13
	 * 6 = 6    E = 14
	 * 7 = 7    F = 15
   */
  	
	double dec; /* the decimal value of the conversion process so far */
  	int i; /* for running through the string */
	double hexval[len-1], hexpow[len-1]; /* should be the right size arrays for the value and power of each character to convert */
  /* calculate the values independantly, then return the calculated int value */
	
	dec = 0;
	for (i = 0; i < len - 1; i++)
	{
/*		printf("h[%d] = %c, %c\n",i, h[i], upper(h[i])); */
		/* determine the value of each character in the string */
		/* should be a switch/case block, since we're basically getting chars to look at */
		switch(upper(h[i]))
		{
			case 'A' :
			/* put the value of the position into an array, along with the exponent to use for it */
				hexval[i] = 10;
				hexpow[i] = len - (i + 2);
				break;
			case 'B' :
				hexval[i] = 11;
				hexpow[i] = len - (i + 2);
				break;
			case 'C' :
				hexval[i] = 12;
				hexpow[i] = len - (i + 2);
				break;
			case 'D' :
				hexval[i] = 13;
				hexpow[i] = len - (i + 2);
				break;
			case 'E' :
				hexval[i] = 14;
				hexpow[i] = len - (i + 2);
				break;
			case 'F' :
				hexval[i] = 15;
				hexpow[i] = len - (i + 2);
				break;
			case '1' :
				hexval[i] = 1;
				hexpow[i] = len - (i + 2);
				break;
			case '2' :
				hexval[i] = 2;
				hexpow[i] = len - (i + 2);
				break;
			case '3' :
				hexval[i] = 3;
				hexpow[i] = len - (i + 2);
				break;
			case '4' :
				hexval[i] = 4;
				hexpow[i] = len - (i + 2);
				break;
			case '5' :
				hexval[i] = 5;
				hexpow[i] = len - (i + 2);
				break;
			case '6' :
				hexval[i] = 6;
				hexpow[i] = len - (i + 2);
				break;
			case '7' :
				hexval[i] = 7;
				hexpow[i] = len - (i + 2);
				break;
			case '8' :
				hexval[i] = 8;
				hexpow[i] = len - (i + 2);
				break;
			case '9' :
				hexval[i] = 9;
				hexpow[i] = len - (i + 2);
				break;
			case '0' :
				hexval[i] = 0;
				hexpow[i] = len - (i + 2);
				break;
			case '\0':
				break;
			default :
				break;
		}
	}
	/* so now we need math.h */
	for (i = 0; i < len - 1; ++i)
	{
/*		printf("hexval[%d] = %f\nhexpow[%d] = %f\n",i,hexval[i],i,hexpow[i]); */
		dec = dec +  ( (double) hexval[i] * pow(16, (double) hexpow[i]));
	}

	return dec;

}

char upper(int c)
{
	int upperdiff; /* value between upper and lower letters */
	upperdiff = 97 - 65; /* difference between 'a' and 'A' */

	if ((c <= 122) && (c >= 97)) /* between lower 'z' and 'a' */
		c = (c - upperdiff);
	
	return c;
}

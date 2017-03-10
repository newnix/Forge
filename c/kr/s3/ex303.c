/* 
 * Exercise 3-3 in K&R's ANSI C
 * found on page 63
 * meant to write a function called expand(s1,s2)
 * where a given string such as a-z is expanded to the entire alphabet
 * should be able to handle cases like a-z0-9 and -a-z
 * leading or trailing -'s are meant to be taken as literal chars
 * rather than ranges.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/get_line.h"

/* set the input string limit */
#define MAX 100
/* set the output string to be 26x the input size */
#define OMAX 2600

/* create expand() prototype */
void expand(char input[], char expand[]);
/* check the block of input to see if we have an expansion */
int isexpansion(char x, char y, char z);
/* define a character class based off the arguments given */
int class(char x, char y);

int main()
{
	char instr[MAX]; /* input from user */
	char ostr[OMAX]; /* output string */
	int len;

	len = get_line(instr,MAX);
	printf("caputured: %s\n",instr);
	expand(instr,ostr); /* expand the string */
	printf("Expanded:\n%s\n",ostr); /* should be fine... or do nothing special */
	return 0;
}

void expand(char input[], char expand[])
{
  int i, j; /* set up our indexes */
  int t; /* transient value for range stepping */
  i = j = t = 0;
  for (i = 0; (input[i] != 0 && input[i] != '\n'); i++)
  {
    /* search for a range such as 'a-z' */
    /* once found, print all values from lvalue -> rvalue */
    /* at each new char placed into *expand, increment j */
    /* upon reaching the outermost loop again, increment j */
    switch (isexpansion(input[i], input[i+1], input[i+2]))
    {
      case 1:
				if (input[i] > input[i+2])
				{
					for (t = input[i]; t >= input[i+2]; t--)
					{
						expand[j] = t;
						j++;
					}
					/* This puts us at the value of input[i+2], add 2 to i here to avoid reprinting expansion chars */
					i += 2;
				}
				else if (input[i] < input[i+2])
				{
					for (t = input[i]; t <= input[i+2]; t++)
					{
						expand[j] = t;
						j++;
					}
					/* This puts us at the value of input[i+2], add 2 to i here to avoid reprinting expansion chars */
					i += 2;
				}
				else
				{
					/* this should mean that input[i] == input[i+2] */
					expand[j] = input[i];
					/* to avoid simply reprinting the expansion chars, skip 2 on the input stream */
					i += 2;
					break;
				}
        break;
      default:
        expand[j] = input[i];
        break;
    }
    j++;
  }
  expand[j+1] = 0; /* ensure we have a NULL byte terminator */
}

int isexpansion(char x, char y, char z)
{
	/* check to see if there's an expandable expression */
	if (y == '-' && z != '\n' && z != 0)
	{
		/* decide how to proceed based on the value of x */
		switch (class(x,z))
		{
			/* search for upper, lower, or numeric value */
			case 1: /* numbers found */
				return 1;
			case 2: /* uppercase found */
				return 1;
			case 3: /* lowercaes found */
				return 1;
			default: /* doesn't match any defined character classes */
				return 5;
		}
	}
	else 
	{	/* not an expandable expression */
		return 9;
	}
}

int class(char x, char y)
{
	/* determine which class of characters a given range belongs to */
	if (x <= 57 && x >= 48)
	{
		if (y <= 57 && y >= 48)
			return 1; /* numbers */
	}
	else if (x <= 90 && x >= 65)
	{
		if (y <= 90 && y >= 65)
			return 2; /* uppercase */
	}
	else if (x <= 122 && x >= 97)
	{
		if (y <= 122 && x >= 97)
			return 3; /* lowercase */
	}
	return 18; /* no matching class */
}

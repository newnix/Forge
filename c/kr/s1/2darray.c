/* 
 * This is a practice program to assign, write to, and read from a 2D array
 */

#include <stdio.h>
#include "../headers/get_line.h"
#include <stdlib.h>

#define MAX 10

int main()
{
	/* first we need to set up the array(s) */
	int d[10][MAX]; /* hold up to 10 MAX length strings */
	int x,y; /* length of the input string */

	/* somehow grab the stuff from the user and stuff it in the array */
	for (x = 0; x < 10; x++)
	{
		/* and another, nested loop */
		for (y = 0; y < MAX; y++)
		{
			d[x][y] = y; /* basically just store where we are right now */
		}
	}
	/* do it again, but this time print the stuff out */
	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < MAX; y++)
		{
			printf("d[%d][%d] = %d\n",x,y,d[x][y]); /* according to valgrind, there's a leak here */
		}
	}
	for (x = 0; x < MAX; x++)
	{
		free(d[x]);
	}
	free (d);
	return 0;
}

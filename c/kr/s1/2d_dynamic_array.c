/* 
 * This is an example of a dynamically allocated
 * 2D array as described by the forum post found here:
 * https://www.gidforums.com/t-4785.html
 * Hopefully this can help with the issues I've had 
 * handling arrays and pointers recently.
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i; /* loop index vars */
	int j;

	int **a; /* pointer notation for a 2D array */
	int size_x; /* first dimension */
	int size_y; /* second dimension */

	/* suppose we have an array of int: a[5][3] */
	size_x = 5;
	size_y = 3;

	/* allocate storage for an array of pointers */
	a = malloc(size_x * sizeof(int *));

	/* for each pointer, allocate storage for an array of ints */
	for (i = 0; i < size_x; i++) 
	{
		a[i] = malloc(size_y * sizeof(int));
	}

	/* this part will show the addresses being used */
	/* and assign arbitrary values to the elements */
	for (i = 0; i < size_x; i++)
	{
		for (j = 0; j < size_y; j++)
		{
			printf("&a[%d][%d] = %p\n", i, j, &a[i][j]); /* shows the addresses of the array elements */
			a[i][j] = i * size_y + j; /* just an easy way to get a unique value for each address */
		}
		printf("\n");
	}

	/* now we show the contents that were assigned */
	for (i = 0; i < size_x; i++)
	{
		for (j = 0; j < size_y; j++)
		{
			printf("&a[%d][%d] = %2d\n", i, j, a[i][j]);
		}
		printf("\n");
	}

	/* now for each pointer, we'll free its array of ints */
	for (i = 0; i < size_y; i++)
	{
		free(a[i]);
	}
	/* now we free the array of pointers */
	free (a);

	return 0;
}

/* according to valgrind, this still has memory issues, I have no idea what's going on */

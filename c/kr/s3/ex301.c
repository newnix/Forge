/* 
 * Exercise 3-1 from K&R's ANSI C 
 * found on page 58
 * meant to create a new version of the binary search function with
 * only one test per loop iteration.
 */

#include <stdio.h>
#include <stdlib.h>

/* binsearch2 prototype */
int binsearch2(int x, int v[], int n);

int main()
{
	int x, n;
	int v[100-1];
	x = 10;
	n = 100;

	for (n = 0; n < 101; n++)
	{
		v[n] = n;
	}

	printf("binsearch2(x, v[], n) = %d\n",binsearch2(x,v,n));
	return 0;
}

int binsearch2(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low < high)
	{
		mid = (low + high) /2;
		if (v[mid] == x)
		{
			return v[mid];
		}
		/*
		 * I'm pretty sure this will miss some targets, 
		 * much like using low++ did, but this is one example
		 * of reducing the tests in the loop. 
		 * The speed difference was negligable.
		 */
		else
			high--;
	}
	return -1; /* no match found */
}

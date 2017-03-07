/*
 * binsearch, example program to be modified in exercise 3-1
 * found on page 58 in K&R's ANSI C Programming Language
 */

#include <stdio.h>
#include <stdlib.h>

/* binsearch prototype */
/* find x in v[0] <= v[1] .. <= v[n-1] */
int binsearch(int x, int v[], int n);

int main()
{
  /* declare a few vars for use in the binsearch function */
  int x, n;
  int v[100-1];
  x = 10;
  n = 100;

	for (n = 0; n < 101; n++)
	{
		v[n] = n;
	}

  printf("binsearch(x, v[], n) = %d\n",binsearch(x,v,n));
  return 0;
}

int binsearch(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;

  while (low <= high)
  {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else /* found match */
      return mid;
  }
  return -1; /* no match */
}

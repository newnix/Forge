/*
 * example 1.2, starting with vars and loops
 * this is meant to just print the farenheight and centigrade temps side-by-side
 */

#include <stdio.h>

int main()
{
	int fahr, cent;
	int lower, upper, step;

	lower = 0;	/* lower limit of temp table */
	upper = 300; /* upper limit of temp table */
	step = 10; /* step size */

	fahr = lower;
	while (fahr <= upper)
	{
		cent = 5 * (fahr - 32) / 9;
		printf("%d\t%d\n", fahr, cent);
		fahr = fahr + step;
	}

	return 0;
}

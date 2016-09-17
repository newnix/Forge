/*
 * example 1.2, starting with vars and loops
 * this is meant to just print the farenheight and centigrade temps side-by-side
 */

#include <stdio.h>

int main()
{

	/* 
	 * Revision 2 of this program, this time using floats instead of ints
	 */

	float fahr, cent;
	float lower, upper, step;

	lower = 0;	/* lower limit of temp table */
	upper = 300; /* upper limit of temp table */
	step = 10; /* step size */

	fahr = lower;
	while (fahr <= upper)
	{
		
		/*
		 * Due to the data type change, the printf strings need modifications as well.
		 */
		
		cent = 5 * (fahr - 32) / 9;
		/* no decimal points for fahr, as it's computed in whole steps. 2 decimal points for cent */
		printf("%.f\t%.2f\n", fahr, cent);
		fahr = fahr + step;
	}

	return 0;
}

/* Tempuratures again, this time with functions! */
#include <stdio.h>

/* re-writing example 1.2 */

/* forward declaration of the function */
float fahr2cent(float t);

main()
{
	float fahr, cent;
	float lower, upper, step;

	lower = -140; /* lower limit of the temp value */
	upper = 140; /* upper limit of the temp value */
	step = 5; /* step size */

	fahr = lower; 
	while (fahr <= upper)
	{
		cent = fahr2cent(fahr);
		/* remember that doubles have a different printf() format */
		printf("%.2f\t%.2f\n",fahr, cent);
		fahr = fahr + step;
	}
}

float fahr2cent(float t)
{
	/*
	 * this function assumes that the value passed to it is a tempurature in fahrenheit
	 * it then performs the necessary calculation for the value to be displayed as centigrade temps
	 * and returns the value of the centigrade temp as a float.
	 */

	return (5 * (t - 32) / 9);
}

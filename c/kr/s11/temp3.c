/* variant of the temp.c program using symbolic substitutions via define */

#include <stdio.h>

#define UPPER 300 /* upper temp limit */
#define LOWER -300 /* lower temp limit */
#define STEP 20 /* step size */

/* now do the loopy thing to print the table */
int main()
{
	int fahr; /* fahrenheight variable */

	for (fahr = LOWER; fahr <= UPPER ; fahr = fahr + STEP )
		printf("%3d %6.2f\n", fahr, (5.0/9.0)*(fahr-32));

	return 0;
}

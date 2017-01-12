/* count the chars from stdin */
#include <stdio.h>

/* rev2, using a for loop this time */
main()
{
	double nc; /* replaced long with double */

	for (nc = 0; getchar() != EOF; ++nc);
	/* this seems odd, but I guess it makes sense as there's no real action taken */
	printf("%.0f\n",nc);
}

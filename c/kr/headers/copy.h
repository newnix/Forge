#ifndef COPY_H
#define	COPY_H

void copy(char from[], char to[])
{
	/* this doesn't do any bounds-checking
	 * it's entirely up to you to ensure overflows don't happen
	 */
	
	int i; /* our iterator */

	/* this should allow us to not worry about the string length at all */
	for (i = 0; from[i] != 0; i++)
	{
		to[i] = from[i];
		/*printf("to[%d]: %c\t from[%d]: %c\n",i,to[i],i,from[i]); uncomment for help debugging */
	}
	to[i+1] = 0;
}

#endif

/* this is exercise 1-12, the target is to take stdin and print it to stdout one word per line */
#include <stdio.h>

#define IN 1 /* in a word */
#define OUT 0 /* out of a word */

/*
 * The general means of taking care of this 
 * would be to find a way to isolate the text surrounded by whitespace characters
 * such as '\t', '\n', and ' '. 
 */

main()
{
	int c,word,state;

	state=OUT; /* default to being outside a word */

	while ((c = getchar()) != EOF)
	{
		/* I'm feeling like a test similar to the minimal wc 
		 * program would be best here, then while the character entered is NOT
		 * one of the values defining a word boundary, we dump the value into 'word'
		 */
		if ( c != ' ' && c != '\t' && c != '\n' ) 
		{
			state = IN;
			putchar(c);
		}
		else
		{
			if (state == IN)
			{
				state = OUT;
				putchar('\n');
			}
		}

	}
}

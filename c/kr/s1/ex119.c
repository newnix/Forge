/* Excersize 1.19
 * found on page 31 of K&R's ANSI C
 * this is meant to reverse a string taken from stdin
 */

#include <stdio.h>

/* define max string size */
#define MAX 1000 /* I'm not going to deal with larger strings */

/* getline function forward declaration */
int getline(char s[], int lim);
/* reversal function */
void reverse(char s[], int len, char r[]);

int main()
{
	/* vars for main() */
	char str[MAX], rts[MAX]; /* string and reverse string */
	int len;	/* length of the string 'str' */
	len = 0;
	while ((len = getline(str, MAX)) > 0)
	{
		printf("%s\n",str);
		reverse(str, len, rts);
		printf("%s\n",rts);
	}
	return 0;
}

int getline(char s[], int lim)
{
	int c,i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
	{
		s[i] = c;
	}
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void reverse(char s[], int len, char r[])
{
	int i;	/* track the decrement of str and increment of rts */
	int o,m;
	i = len;
	m = 0;
	for (o = 1 ; (i-o) >= 0; ++o )
	{
		r[m] = s[o];
		/* show me the process */
		printf("i=%d\ts[%d] = %c\tr[%d] = %c\n",o,o,s[o],o,r[o]);
		++m;
	}
	r[i+1] = '\0';
}


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
	char str[MAX],rts[MAX]; /* string and reverse string */
	int len;	/* length of the string 'str' */
	int dbg = 0;
	len = 0;

	while ((len = getline(str, MAX)) > 0)
	{
		printf("%s\n",str);
		for (dbg = 0; dbg < len; dbg++)
		{
			printf("str[%d] = %c\n",dbg,str[dbg]);
		}
		reverse(str,len,rts);
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
	int l;
	l = len;

	for (i=1; i <= l; i++)
	{
		
		r[i] = s[l-i];
		/* show me the process */
		printf("s[%d] = %c\tr[%d] = %c\n",l-i,s[l-i],i,r[i]);
	}
	i++;
	r[i]='\0';
}

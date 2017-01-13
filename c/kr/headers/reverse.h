#ifndef REVERSE_H
#define REVERSE_H

void reverse(char s[], int len, char r[])
{
	int i; /* tracks string position */
	int l;
	/* meant to discard the newline and null chars at the end of a string */
	l = (len - 2);

	/* loop through and copy s[] into r[] in reverse */
	for (i = 0; i <= l; i++)
	{
		r[i] = s[l - i];
		/* uncomment to have printf() show the progress of running through the string */
		/* printf("s[%d] = %c\tr[%d] = %c\n",l-i,s[l-i],i,r[i]); */
	}
	r[i] = '\0';
}

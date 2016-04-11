// Learn C the hard way exercise 4
// this is meant to introduce the tool "valgrind"

#include <stdio.h>

/* warning: this program is wrong on purpose */

int main()
{
    int age = 10;
    int height;

    printf("I am %d years old.\n");
    printf("I am %d inches tall.\n",height);

    return 0;
}

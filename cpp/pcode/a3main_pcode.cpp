// Design Draft of Assignment 3
// Needs to translate a string to morse code

#include <iostrea>
#include <cctype>
#include <string>

int main()
{
    create variables to hold the string

    ask user for a string to convert to morse

    run toMorse(string);

    display the resulting string of Morse characters

    return 0;
}

string toMorse(string)
{
    take the string and create a cstring from it

    compare the characters in the cstring to Morse characters

    swap the characters in the cstring with the morse characters

    return the modified cstring
}

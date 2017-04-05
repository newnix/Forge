// Practice program 14-9
// Found on page 832
// Demonstrates the feetInches class overloaded prefix and postfix ++ operator

#include <iostream>
#include "feetInches.h"

using namespace std;

int main()
{
    int count; // loop counter

    // Define a feetInches object with the default value of 0,0 
    feetInches first;

    // Define a feetInches object with 1ft 5in
    feetInches second(1.5);

    // Use the prefix ++ operator
    cout << "Demonstrating prefix ++ operator. \n";
    for (count = 0; count < 12; ++count)
    {
        first = ++second;
        cout << "First: " << first.getF() << " feet, ";
        cout << first.getI() << " inches. ";
        cout << "Second: " << second.getF() << " feet, ";
        cout << second.getI() << " inches. \n";
    }

    // Use the postfix ++ operator
    cout << "Demonstrating postfix ++ operator. \n";
    for (count = 0; count < 12; count++)
    {
        first = second++;
        cout << "First: " << first.getF() << " feet, ";
        cout << first.getI() << " inches.";
        cout << "Second: " << second.getF() << " feet, ";
        cout << second.getI() << " inches.\n";
    }

    return 0;
}

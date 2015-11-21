// Practice program 14-8
// Found on page 830
// This program demonstrates the overloaded '-' and '+' operators

#include <iostream>
#include "feetInches.h"

using namespace std;

int main()
{
    int feet, inch; // Hold the input for feet and inch

    // Create three feetInches objects. 
    // Default args for constructors will be used.
    feetInches first, second, third;

    // Get a distance from the user
    cout << "Enter a distance in feet and inches: ";
    cin >> feet >> inch;

    // Store the distance in the first object
    first.setFeet(feet);
    first.setInch(inch);

    // Get another distance
    cout << "Enter another distance in feet and inches: ";
    cin >> feet >> inch;

    // Store the distance in second
    second.setFeet(feet);
    second.setInch(inch);

    // Assign first + second to third
    third = first + second;

    // Display the results
    cout << "First + Second = ";
    cout << third.getF() << " feet, ";
    cout << third.getI() << " inches. \n";

    // Assign first - second to third
    third = first - second;

    // Display the results again
    cout << "First - Second = ";
    cout << third.getF() << " feet, ";
    cout << third.getI() << " inches.\n";

    return 0;
}


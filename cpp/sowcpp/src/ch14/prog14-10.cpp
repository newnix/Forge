// Practice program 14-10
// Found on page 835
// Demonstrates overloading the '>', '<', and '==' operations

#include <iostream>
#include "feetInches.h"

using namespace std;

int main()
{
    int feet, inch; // Hold the feet/inch values

    // Create two feetInches objects. Use the default contructor.
    feetInches first, second;

    // Get a distance from the user.
    cout << "Enter a distance in feet and inches, separated by spaces: ";
    cin >> feet >> inch;

    // Store the distances in first
    first.setFeet(feet);
    first.setInch(inch);

    // Get another distance from the user.
    cout << "Enter another distance in feet and inches, separated by spaces: ";
    cin >> feet >> inch;

    // Store the second distance in, you guessed it, second
    second.setFeet(feet);
    second.setInch(inch);

    // Compare the two objects
    cout << "Comparing the two distances...\n\n";
    if (first == second)
    {
        cout << "The two distances are equal." << endl;
    }
    if (first < second)
    {
        cout << "The first distance is shorter than the second." << endl;
    }
    if (first > second)
    {
        cout << "The second distance is shorter than the first." << endl;
    }

    return 0;
}

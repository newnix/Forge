// This program demonstrates memberwise assignment.
// Practice Program 14-5 found on page 812

#include <iostream>
#include "rectanglev4.h"

using namespace std;

int main()
{
    // Define the two rectange objects
    rectangle box1(10.0, 10.0); // length and width of 10.0
    rectangle box2(20.0, 20.0); // length and width of 20.0

    // Display each object's width and length
    cout << "box1's width and length: " << box1.getw() << " " << box1.getl() << endl;
    cout << "box2's width and length: " << box2.getw() << " " << box2.getl() << endl;

    // Assign the members of box1 to box2
    box2 = box1;

    // Display each object's length and width again
    cout << "box1's width and length: " << box1.getw() << " " << box1.getl() << endl;
    cout << "box2's width and length: " << box2.getw() << " " << box2.getl() << endl;

    return 0;
}

// Practice program 13-6 on page 740
// Demonstrates a header file and constructor

#include "rectangle.h"
#include <iostream>

using namespace std;

int main()
{
    rectangle box;  // rectangle instance

    // Display the rectangle's data

    cout << "Here's the rectangle's data:" << endl;
    cout << "Length: " << box.getl() << endl;
    cout << "Width: " << box.getw() << endl;
    cout << "Area: " << box.geta() << endl;

    return 0;
}

// Practice program 15-5
// found on page 888
// This program demonstrates passing arguments to a base class constructor

#include <iostream>
#include "cube.h"

using namespace std;

int main()
{
    double cubew;   // Width of the cube object
    double cubel;   // Lenth of the cube object
    double cubeh;   // Hight of the cube object

    // Get the length, width, and height of the cube from the user.
    cout << "Enter the dimensions of a cube \n";
    cout << "Width: ";
    cin >> cubew;
    cout << "Length: ";
    cin >> cubel;
    cout << "Height: ";
    cin >> cubeh;

    // Define a cube object using the user given dimensions
    cube myC(cubeh, cubel, cubew);

    // Display the user's cube... Rectangular prism.
    // This book keeps saying cube and it's difficult to not retype that verbatim.
    // A cube would only take one argument, then multiply it by itself three times.
    // A cube will be demonstrated in a different set of functions. 
    // A rectangular prism is what we're making here, because the three dimensions aren't necessarily the same.
    cout << "Here are the \"Cube's\" properties:\n";
    cout << "Width: " << myC.getw() << endl;
    cout << "Length: " << myC.getl() << endl;
    cout << "Height: " << myC.geth() << endl;
    cout << "Volume: " << myC.getv() << endl;
    cout << "Base Area: " << myC.geta() << endl;

    return 0;
}

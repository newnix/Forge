// Practice program 11-7 found on page 616
// This program uses a function to return parts of a data structure
// This is a modification of prog11-2

#include <iostream>
#include <iomanip>
#include <cmath>    // To have access to the "pow" function
using namespace std;

// Constant for PI
const double PI = 3.14159;

// Structure declaration
struct circle
{
    double radius;  // The radius
    double diameter;    // The diameter
    double area;    // The area
};

// Function Prototypes
circle getinfo();

int main()
{
    circle c;   // Define a structure variable

    // Get some data about the circle
    c = getinfo();

    // Calculate the circle's area
    c.area = PI * pow(c.radius, 2.0);

    // Display the circle data
    cout << "The radius and the area of the cirlce are: \n";
    cout << fixed << showpoint << setprecision(2);
    cout << "Radius: " << c.radius << endl;
    cout << "Area: " << c.area << endl;

    return 0;
}

/*
 * Definition of the function getinfo.
 * This uses a local variable, tempC, which is a circle structure
 * The user enters the diameter of the circle, which is stored in the tempC.diameter
 * The function then calculates the radius which is stored in tempC.radius
 * tempC is then returned from the function.
 */

circle getinfo()
{
    circle tempC;   // Temporary structure value

    // Store the circle data in the temporary variable.
    cout << "Enter the diameter of a circle: ";
    cin >> tempC.diameter;
    tempC.radius = tempC.diameter / 2.0;

    // Return the temporary variable
    return tempC;
}

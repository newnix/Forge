// Practice program 11-2 found on page 601
// Using data structures to describe a circle

#include <iostream>
#include <cmath>    // for the "pow" function
#include <iomanip>
using namespace std;

// Constant for pi
const double PI = 3.14159;

// Structure declaration of a circle
struct circle
{
    double radius;      // The radius
    double diameter;    // The diameter
    double area;        // The area
};

int main()
{
    circle c;   // Defining a structure variable

    // Get the circle's diameter
    cout << "Enter the diameter of a circle: ";
    cin >> c.diameter;

    // Calculate the circle's radius
    c.radius = c.diameter / 2;

    // Calculate the area
    c.area = PI * pow(c.radius, 2.0);

    // Display the circle data
    cout << fixed << showpoint << setprecision(2);
    cout << "The radius and area of the circle are: \n";
    cout << "Radius: " << c.radius << endl;
    cout << "Area: " << c.area << endl;

    return 0;
}

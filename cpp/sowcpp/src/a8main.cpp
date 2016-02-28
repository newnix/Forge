// Assignment 8 source code

#include <iostream>
#include <iomanip>
#include "circle.h"
#include "rectangle.h"

using namespace std;

int main()
{
    // Declare a couple of variables for shape parameters
    long x; // Circle x value
    long y; // Circle y value
    double r;   // Circle radius
    long w; // Rectangle width
    long l; // Rectangle length

    // Declare a blank circle and rectangle object
    rectangle rect;
    circle circ;

    // Get the imput from the user
    // Assign input to the relevant shapes
    cout << "This program calculates the area of a shape."<< endl;
    cout << "First we'll create a circle." << endl;
    cout << "Please enter the radius: ";
    cin >> r;
    circ.setRadius(r);
    cout << "What's the X coordinate of the circle's centerpoint? ";
    cin >> x;
    circ.setX(x);
    cout << "And the Y coordinate of the circle's centerpoint? ";
    cin >> y;
    circ.setY(y);
    cout << endl << "Now for a rectangle."<< endl;
    cout << "Please enter the width of the rectangle: ";
    cin >> w;
    rect.setWidth(w);
    cout << "And the length: ";
    cin >> l;
    rect.setLength(l);
    
    // Calculate the areas
    // print the areas to stdout.

    rect.calcArea();
    
    cout << fixed << setprecision(2) << showpoint;
    cout << "The circle is centered around the point (" << circ.getX() << ", " << circ.getY() << ")." << endl;
    cout << "With a radius of " << circ.getRadius() << " units, and area of " << circ.getArea() << " square units.\n";
    cout << endl;
    cout << endl;
    cout << "The rectangle has a length of " << rect.getLength() << " units and width of " << rect.getWidth() << " units.";
    cout << "The rectangle has an area of " << rect.getArea() << " square units." << endl;

    return 0;
}

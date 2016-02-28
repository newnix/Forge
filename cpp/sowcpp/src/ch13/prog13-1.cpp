// Practice Program 13-1 on page 718
// This program demonstrates the basic class of a rectangle

#include <iostream>

using namespace std;

// Rectangle class declaration
class rectangle
{
    private:
        double width;
        double length;

    public:
        void setwidth(double);
        void setlength(double);
        double getwidth() const;
        double getlength() const;
        double getarea() const;
};

/*
 * setwidth assigns a value to the width member
 */

void rectangle::setwidth(double w)
{
    width = w;
}

/*
 * setlength assigns a value to the length member
 */

void rectangle::setlength(double l)
{
    length = l;
}

/*
 * getwidth returns the value in the width member
 */

double rectangle::getwidth() const
{
    return width;
}

/*
 * getlength returns the value in the length member
 */

double rectangle::getlength() const
{
    return length;
}

/*
 * get the area of the recangle
 */

double rectangle::getarea() const
{
    return width * length;
}

/*
 * main function
 */

int main()
{
    rectangle box;  // Define an instance of the rectangle class
    double rectw;   // Variable for the box width
    double rectl;   // Variable for the box length

    // Get the length and width from the user

    cout << "This program will calulate the area of a rectangle." << endl;
    cout << "What is the width?: ";
    cin >> rectw;
    cout << "What is the length?: ";
    cin >> rectl;

    // Store the width and length in the box object.

    box.setwidth(rectw);
    box.setlength(rectl);

    // Display the rectangle's data

    cout << "Here's  the rectangle's data:" << endl;
    cout << "Width: " << box.getwidth() << endl;
    cout << "Length: " << box.getlength() << endl;
    cout << "Area: " << box.getarea() << endl;

    return 0;
}

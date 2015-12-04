// Pseudocode for assignment 8.

#include <iostream>
#include <iomanip>
#include "shapes.h"

using namespace std;

int main()
{
    class shapes
    {
        private: 
            double area;
        public:
            // Accessor
            double getArea() const
            {
                return area;
            }

            // Calculate the area
            virtual void calcArea() const;

            // Return the area
            virtual double getA() const;
    }

    // Derived class
    class circle : public shapes
    {
        private:
            long centerx;   // X variable for the center
            long centery;   // Y variable for the center
            double radius;  // radius of the circle
        public:
            // default constructor
            cirlcle()
            {
                radius = 0.0;
                centerx = 0;
                centery = 0;
            }

            // Constructor with arguments
            circle(int x, int y, double r)
            {
                radius = r;
                centerx = x;
                centery = y;
            }
            
            // Calculate the area
            virtual void calcArea() const
            {
                area = (3.14159 * radius * radius);
            }

            // Return the center coordinates
            long getx() const
            {
                return centerx;
            }

            long gety() const
            {
                return centery;
            }

            virtual double getA() const
            {
                return area;
            }
            
    }

    // Derived class again, different shape
    class rectangle : public shapes
    {
        private:
            long width; // The width of the rectangle
            long length;    // Length of the rectangle
        public:
            // Default constructor
            rectangle()
            {
                width = 0.0;
                length = 0.0;
            }

            // Constructor with arguments
            rectangle(long w, long l)
            {
                width = w;
                length = l;
            }

            // Accessors
            long getw() const
            {
                return width;
            }

            long getl() const
            {
                return length;
            }

            // Calculate the area
            virtual void calcArea() const
            {
                area = (width * length);
            }
            
            virtual double getA() const
            {
                return area;
            }

    }

    // Declare a couple of variables for shape parameters
    long x; // Circle x value
    long y; // Circle y value
    double r;   // Circle radius
    long w; // Rectangle width
    long l; // Rectangle length

    // Get the imput from the user
    // Assign input to the relevant shapes

    // Calculate the areas
    // print the areas to stdout.

    return 0;
}

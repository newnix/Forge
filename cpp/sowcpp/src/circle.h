// Circle class definition
// derived from the shapes class

// Header guard
#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class circle : public shapes
{
    private:
        double PI = 3.14159;    // Approximate value of pi
        double radius;                       // Holds the radius of the circle
        long centerX;                        // Center point x value
        long centerY;                        // Center point y value
    public:
        // Default Constructor
        circle()
        {
            centerX = 0;
            centerY = 0;
            radius = 0.0;
            calcArea();
        }

        // Constructor
        circle(double r, long x, long y)
        {
            centerX = x;
            centerY = y;
            radius = r;
            calcArea();
        }

        // Mutator functions
        void setRadius(double r) 
        {
            radius = r;
            calcArea();
        }

        void setX(long x)
        {
            centerX = x;
        }

        void setY(long y)
        {
            centerY = y;
        }

        // Accessors
        double getRadius() const
        {
            return radius;
        }

        long getX() const
        {
            return centerX;
        }

        long getY() const
        {
            return centerY;
        }

        // Redefined calcArea()
        void calcArea()
        {
            area = (PI * radius * radius);
        }
};
#endif

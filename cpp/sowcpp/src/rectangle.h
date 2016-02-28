// Rectangle definition
// Derived class from the shape class

// Header guard
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class rectangle : public shapes
{
    private:
        long width; // Rectangle width
        long length;// Rectangle length
    public:
        // Default constructor
        rectangle()
        {
            width = 0;
            length = 0;
            calcArea();
        }

        // Constructor
        rectangle(long w, long l)
        {
            width = w;
            length = l;
            calcArea();
        }

        // Accessor functions
        long getWidth() const
        {
            return width;
        }

        long getLength() const
        {
            return length;
        }

        // Mutator functions
        void setWidth(long w)
        {
            width = w;
        }

        void setLength(long l)
        {
            length = l;
        }

        // Define the calcArea function for rectangles
        void calcArea()
        {
            area = (length * width);
        }
};
#endif

// Practice header file for cubes
// derived class from rectangles.
// Found on page 886 as well.

// Header guard
#ifndef CUBE_H
#define CUBE_H

// Include the rectangle header file
// to bring in the rectangle class.
#include "rectangle.h"

class cube : public rectangle
{
    protected:
        double height;  // add a dimension to the rectangle, making it 3D
        double volume;  // holds the volume of the cube, or more accurately, the rectangular prism.

    public:
        // Default constructor
        cube() : rectangle()
        {
            height = 0.0;   // keep the cube a 2D rectangle
            volume = 0.0;   // not 3D? no volume, duh.
        }

        // Constructor with args
        cube(double h, double l, double w) : rectangle(w, l)    // creates a cube based on the created rectangle
        {
            height = h;
            volume = (geta() * h);
        }

        // Accessor functions
        double geth() const
        {
            return height;
        }

        double getv() const
        {
            return volume;
        }
};
#endif

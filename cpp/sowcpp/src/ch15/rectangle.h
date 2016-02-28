// Rectangle class header file
// found on page 886

// Header guard
#ifndef RECTANGLE_H
#define RECTANGLE_H

class rectangle
{
    private:
        double width;   // Width of the rectangle
        double length;  // Length of the rectangle

    public:
        // Default constructor
        rectangle()
        {
            width = 0.0;
            length = 0.0;
        }

        // Constructor that accepts arguments
        rectangle(double w, double l)
        {
            width = w;
            length = l;
        }

        // Accessor functions
        double getw() const
        {
            return width;
        }

        double getl() const
        {
            return length;
        }

        double geta() const
        {
            return (width * length);
        }
};
#endif

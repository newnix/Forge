// Header file for the generic shape class
// Allows for derived classes of rectangle and circle to be spawned

// Header guard
#ifndef SHAPES_H
#define SHAPES_H

class shapes
{
    protected:
        double area;    // Holds the area of the shape
    public:
        // Default constructor
        shapes()
        {
            area = 0.0;
        }
        
        // Accessor 
        double getArea() const
        {
            return area;
        }

        // Calculate the area
        // allow the function to be redefined by the relevant shape.
        virtual void calcArea() = 0;
        
};
#endif

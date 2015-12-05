// Header file for circle objects

// Header guard, make sure the contents aren't duplicated

#ifndef CIRCLE_H
#define CIRCLE_H

class circle
{
    private:
        float radius;
        float pi = 3.14159;
    public:
        // Construct blank circle
        circle()
        {
            radius = 0.0;
        }

        // Set the radius
        void setr(float r)
        {
            radius = r;
        }

        // Get the area
        float  geta() const
        {
            return pi * radius * radius;
        }

        // Get the circumference
        float getcir() const
        {
            return (2 * pi * radius);
        }

        // Get the diameter
        float getdia() const
        {
            return 2 * radius;
        }

        // Destroy the circle
        ~circle()
        {
        }
};

#endif

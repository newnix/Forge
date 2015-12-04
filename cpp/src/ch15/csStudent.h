// Specification file for the CS Student class
// found on page 923

// Header guard
#ifndef CSSTUDENT_H
#define CSSTUDENT_H

#include "student.h"

// Constants for required hours
const int MATH_HOURS = 20;  // Math hours required
const int CS_HOURS = 40;    // CS hours required
const int GEN_ED_HOURS = 60;    // General education hours

class csStudent : public student
{
    private:
        int mathHours;  // Hours of math taken
        int csHours;    // Hours of cs courses taken
        int genEdHours; // Hours of general education taken
    public:
        // Default constructor
        csStudent() : student()
        {
            mathHours = 0;
            csHours = 0;
            genEdHours = 0;
        }

        // Constructor
        csStudent(string n, string i, int y) : student(n, i, y)
        {
            mathHours= 0;
            csHours = 0;
            genEdHours = 0;
        }

        // Mutator functions
        void setMathHours(int m)
        {
            mathHours = m;
        }

        void setCsHours(int c)
        {
            csHours = c;
        }

        void setGenEdHours(int g)
        {
            genEdHours = g;
        }

        // Overridden getRemainingHours function,
        // defined in csCstudent.cpp
        virtual int getRemainingHours() const;
};
#endif

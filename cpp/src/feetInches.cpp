// Practice source file for feetInches.h
// Found on page 827
// Implements the feetInches.h functions
// This file makes it possible to compare feetInches objects directly,
// By overloading specific comparative functions

#include <cstdlib>  // Needed for "abs()"
#include "feetInches.h"

/*
 * Definition of the member function simplify(). 
 * This function checks for values in the inches member greater than 12 or less than zero.
 * If such a value is found, the numbers in feet and inches are adjusted to conform to a standard feet and inches expression
 * E.G. 150 inches = 12ft 6in.
 */

void feetInches::simplify()
{
    if (inch >= 12)
    {
        feet += (inch / 12);
        inch = inch % 12;
    }

    else if (inch < 0)
    {
        feet -= ((abs(inch) / 12 + 1));
        inch = 12 - (abs(inch) % 12);
    }
}

/*
 * Overloaded binary + operator.
 */

feetInches feetInches::operator + (const feetInches &right)
{
    feetInches temp;
    
    temp.inch = inch + right.inch;
    temp.feet = feet + right.feet;
    temp.simplify();
    return temp;
}

/*
 * Overloaded binary - operator.
 */

feetInches feetInches::operator - (const feetInches &right)
{
    feetInches temp;

    temp.inch = inch - right.inch;
    temp.inch = feet - right.feet;
    temp.simplify();
    return temp;
}

/* 
 * Overloaded binary postfix ++ operation
 */

feetInches feetInches::operator ++ (int)
{
    feetInches temp(feet,inch);
    inch++;
    simplify();
    return temp;
}

/*
 * Overloaded binary prefix ++ operation
 */

feetInches feetInches::operator ++ ()
{
    ++inch;
    simplify();
    return *this;
}

/*
 * Overloading the > operation
 */

bool feetInches::operator > (const feetInches &right)
{
    bool status;

    if ( feet > right.feet)
    {
        status = true;
    }
    else if (( feet == right.feet ) && ( inch > right.inch)) 
    {
        status = true;
    }
    else
    {
        status = false;
    }

    return status;
}

/*
 * Overloading the < operation
 */

bool feetInches::operator < (const feetInches &right)
{
    bool status;

    if (feet < right.feet)
    {
        status = true;
    }
    else if (feet == right.feet && inch < right.inch)
    {
        status = true;
    }
    else
    {
        status = false;
    }

    return status;
}

/*
 * Overloading the == operation
 */

bool feetInches::operator == (const feetInches &right)
{
    bool status;

    if (feet == right.feet && inch == right.inch)
    {
        status = true;
    }
    else
    {
        status = false;
    }

    return status;
}

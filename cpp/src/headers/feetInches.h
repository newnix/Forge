// Practice header file to convert units between feet and inches
// found on page 826

#ifndef FEETINCHES_H
#define FEETINCHES_H

// The feetinches class holds distances or measurements expressed in feet or inches

class feetInches
{
    private:
        int feet;   // To hold the number of feet
        int inch;   // To hold the number of inches
        void simplify();    // Defined in feetInches.cpp
    public:
        // Constructor
        feetInches(int f = 0, int i = 0)
        {
            feet = f;
            inch = i;
            simplify();
        }

        // Mutator functions
        void setFeet(int f)
            { feet = f; }
        void setInch(int i)
            { inch =i; simplify(); }

        // Accesor functions
        int getF() const
            { return feet; }

        int getI() const
            { return inch; }

        // Overloaded operator functions
        feetInches operator + (const feetInches &); // Overloaded +
        feetInches operator - (const feetInches &); // Overloaded -

        // Overloaded ++ operator function (postfix)
        feetInches operator ++ (int);

        // Overloaded ++ operator function (prefix)
        feetInches operator ++ ();

        // Overloading relational operators
        feetInches operator > (const feetInches &);
        feetInches operator < (const feetInches &);
        feetInches operator == (const feetInches &);
};

#endif

// SUV header file, holding the SUV class
// This is based off the automobile class

// Header guard and inclusion files
#ifndef SUV_H
#define SUV_H

#include "automobile.h"
#include <string>

using namespace std;

// The SUV class
class suv : public automobile
{
    private:
        int pass;   // Number of passengers the suv can carry

    public:
        // Default constructor
        suv() : automobile()
        {
            pass = 0;
        }

        // Constructor with arguments
        suv(string sMake, int sModel, int sMileage, double sPrice, int sPass) : automobile(sMake, sModel, sMileage, sPrice)
        {
            pass = sPass;
        }

        // Accessor for the passenger count attribute
        int getPass() const
        {
            return pass;
        }
};
#endif
       

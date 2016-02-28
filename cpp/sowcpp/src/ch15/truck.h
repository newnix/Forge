// Header file for truck specifications
// based on the automobile class

// Header guard andf inclusions
#ifndef TRUCK_H
#define TRUCK_H

#include "automobile.h"
#include <string>

using namespace std;

// The truck class, predictably, represents a truck
class truck : public automobile
{
    private:
        string drive;   // Indicates manual or automatic transmission

    public:
        // Default constructor
        truck() : automobile()
        {
            drive = " ";
        }

        // Constructor with arguments
        truck(string tMake, int tModel, int tMileage, double tPrice, string tDrive) : automobile(tMake, tModel, tMileage, tPrice)
        {
            drive = tDrive;
        }

        // Accessor for the Truck drive type
        string getDrive() const
        {
            return drive;
        }
};
#endif

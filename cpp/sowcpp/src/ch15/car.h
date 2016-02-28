// Car header file
// derived class from the automobile class

// Header guard and inclusion of the automobile class
#ifndef CAR_H
#define CAR_H

#include "automobile.h"
#include <string>

using namespace std;

// Declaration of the car class
// This, quite predictably, represents a car in inventory.

class car : public automobile
{
    private:
        int doors;  // Number of doors the car has

    public:
        // Default constructor
        car() : automobile()
        {
            doors = 0;
        }

        // Constructor with arguments
        car(string carMake, int carModel, int carMileage, double carPrice, int carDoors) : automobile(carMake, carModel, carMileage, carPrice)
        {
            doors = carDoors;
        }

        // Accessor for the car doors
        int getDoors() const
        {
            return doors;
        }
};
#endif

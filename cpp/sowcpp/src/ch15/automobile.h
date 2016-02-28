// Automobile header file on page 890

// Header guard
#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include <string>

using namespace std;

// The automobile class holds general data about an automobile in inventory
class automobile
{
    private:
        string make;    // The make of the automobile
        int model;      // The automobile's year
        int mileage;    // Mileage of the automobile
        double price;   // Cost of the automobile

    public:
        // Default constructor
        automobile()
        {
            make = " ";
            model = 0;
            mileage = 0;
            price = 0.0;
        }

        // Constructor with arguments
        automobile(string amake, int amodel, int amile, double aprice)
        {
            make = amake;
            model = amodel;
            mileage = amile;
            price = aprice;
        }

        // Accessors
        string getMake() const
        {
            return make;
        }

        int getModel() const
        {
            return model;
        }

        int getMile() const
        {
            return mileage;
        }

        double getPrice() const
        {
            return price;
        }
};
#endif

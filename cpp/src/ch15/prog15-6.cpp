// Practice program 15-6, found on page 894
// This demonstrates the car, truck, and suv classes
// derived fram the automobile class

#include <iostream>
#include <iomanip>
#include "car.h"
#include "suv.h"
#include "truck.h"

using namespace std;

int main()
{
    // Create a car object for a used 2007 BMW, with 50kmiles
    // priced at $15k, with 4 doors.
    car car("BMW", 2007, 50000, 15000.0, 4);

    // Create a truck initiated as a used 2006 Toyota
    // with 40k miles, priced at $18k, with 4-wheel drive
    truck truck("Toyota", 2006, 40000, 18000.0, "4WD");

    // Create an suv object initialized as a used 2005 Volvo
    // with 30k miles, priced at $12k, with 5 passenger capacity
    suv suv("Volvo", 2005, 30000, 12000.0, 5);
    
    // Display the automobiles in inventory
    cout << fixed << showpoint << setprecision(2);
    cout << "We have the following car in inventory: \n";
    cout << car.getModel() << " " << car.getMake() << " ";
    cout << "with " << car.getDoors() << " doors, and ";
    cout << car.getMile() << " miles." << endl;
    cout << "Price: $" << car.getPrice() << endl << endl;

    // Display the truck next.
    cout << "We have the following truck in inventory: \n";
    cout << truck.getModel() << " " << truck.getMake() << " ";
    cout << "with " << truck.getDrive() << " drive type and ";
    cout << truck.getMile() << " miles." << endl;
    cout << "Price: $" << truck.getPrice() << endl << endl;

    // Display the suv as well
    cout << "We have the following suv in stock as well:\n";
    cout << suv.getModel() << " " << suv.getMake() << " ";
    cout << "with " << suv.getMile() << " miles, and room for ";
    cout << suv.getPass() << " passengers." << endl;
    cout << "Price: $" << suv.getPrice() << endl << endl;

    return 0;
}

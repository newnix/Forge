// Practice program 15-4 found on page 884
// This program demonstrates the order in which
// Base and derived class contructors and destructors are called

#include <iostream>

using namespace std;

/*
 * Base class declaration
 */

class baseClass
{
    public:
        baseClass() // Constructor
        {
            cout << "This is the base class constructor.\n";
        }

        ~baseClass()    // Destructor
        {
            cout << "This is the base class destructor.\n";
        }
};

/*
 * Derived class declaration
 */

class derivedClass : public baseClass
{
    public:
        derivedClass()  // Constructor
        {
            cout << "This is the derived class constructor.\n";
        }

        ~derivedClass() // Destructor
        {
            cout << "This is the derived class destructor.\n";
        }
};

/*
 * main function
 */

int main()
{
    cout << "We will now define a derivedClass object.\n";

    derivedClass obj;

    cout << "The program is now going to end." << endl;
    
    return 0;
}

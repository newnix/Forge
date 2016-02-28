// Practice program 15-15, found on page 919
// This program demonstrates that only the base class destructor is called
// as the derived class functions go out of scope.

#include <iostream>

using namespace std;

// Animal is a base class
class animal
{
    public:
        // Constructor
        animal()
        {
            cout << "Animal constructor running.\n";
        }

        // Destructor
        ~animal()
        {
            cout << "Animal class destructor running.\n";
        }
};

// The dog class is derived from animal
class dog : public animal
{
    public:
        // Constructor
        dog() : animal()
        {
            cout << "Dog constructor running.\n";
        }

        // Destructor
        ~dog()
        {
            cout << "Dog destructor running.\n";
        }
};

/*
 * main function
 */

int main()
{
    // Create a dog object, referenced by an animal pointer
    animal *myanimal = new dog;

    // Delete the dog object
    delete myanimal;
    
    return 0;
}

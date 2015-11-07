// Practice program 13-10 on page 750
// This demonstrates the use of a destructor

#include <iostream>

using namespace std;

class Demo
{
    public:
        Demo();     // Constructor
        ~Demo();    // Destructor
};

Demo::Demo()
{
    cout << "Welcome to the constructor!" << endl;
}

Demo::~Demo()
{
    cout << "The destructor is now obliterating this object!" << endl;
}

/*
 * main function
 */

int main()
{
    Demo demo;  // demo object
    
    cout << "This program demonstrates an object with a constructor and destructor." << endl;

    return 0;
}

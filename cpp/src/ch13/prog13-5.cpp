// Practice Program 13-5 on page 738
// This program demonstrates the use of constructors

#include <iostream>

using namespace std;

// Demo class declaration

class Demo
{
    public: 
        Demo(); //Constructor
};

Demo::Demo()
{
    cout << "Welcome to the constructor!" << endl;
}

/*
 * main function
 */

int main()
{
    Demo demo;  // demo object 

    cout << "This program demonstrates an object with a constructor." << endl;

    return 0;
}

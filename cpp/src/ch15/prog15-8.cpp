// Practice program 15-8
// found on page 900
// This program demonstrates that when a derived class 
// function overrides a base class function, objects of the base class
// still call the base class version of the function.

#include <iostream>

using namespace std;

class baseClass
{
    public:
        void showMessage()
        {
            cout << "This is the base class." << endl;
        }
};

class dClass : public baseClass
{
    public:
        void showMessage()
        {
            cout << "This is the derived class." << endl;
        }
};

int main()
{
    baseClass b;
    dClass d;

    b.showMessage();
    d.showMessage();

    return 0;
}

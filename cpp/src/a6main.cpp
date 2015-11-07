// Assignment 6
// Use a circle class object

#include "circle.h"
#include <iostream>
#include <cctype>

using namespace std;

int main()
{
    circle cir; // Circle object
    float r;    // Hold user-provided radius
    char again; // Whether or not the user wants to make another circle

    cout << "This program displays information of a circle with a given radius." << endl;
    do
    {
        cout << "\nWhat is the radius?: ";
        cin >> r;

        cir.setr(r);

        cout << "The diameter is : " << cir.getdia() << endl;
        cout << "The area is : " << cir.geta() << endl;
        cout << "The circumference is : " << cir.getcir() << endl;

        cout << endl << "Would you like to calculate another circle? [Y/N]" << endl;
        cin.ignore();
        cin >> again;

    }while (toupper(again) != 'N');

    return 0;
}

// Assginment 6 design doc

#include <iostream>
#include <cctype>
#include "circle.h"

using namespace std;

int main()
{
    circle cir; // Make a circle
    float r;    // Radius
    char again; // Let the user determine whether or not to go again

    do
    {
        get the radius from the user.

        assign the radius to the circle object.

        print the results to stdout

        ask the user if they want to go again
     }while (toupper(again != 'N'));

     return 0;
}

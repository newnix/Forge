// This program demonstrates a static member variable
// Practice program 14-1 on page 801

#include <iostream>
#include "tree.h"

using namespace std;

int main()
{
    // Define three tree objects
    tree oak;
    tree elm;
    tree pine;

    // Display the number of Tree objects we have
    cout << "We have " << pine.getObjectCount () << " trees in our program!";
    cout << endl;

    return 0;
}

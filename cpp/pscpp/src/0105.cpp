// Practice program 05 in ch01 
// Found on p35 of "Problem Solving with C++" 8th edition
// This program is supposed to add and multiply any two given integers

#include <iostream>

int main()
{
    // set up the variables
    int x,y;    // input variables

    // Let the user know what's going on
    std::cout << "Enter an ineger: " << std::endl;
    std::cin >> x;
    std::cout << "\nEnter another integer: " << std::endl;
    std::cin >> y;

    // Calculate and display the results
    std::cout << "\nThe sum of " << x << " and " << y << " is: " << (x+y) << "." << std::endl;
    std::cout << "The product of " << x << " and " << y << " is: " << (x*y) << "." << std::endl;

    // Kill the program
    return 0;
}

// Chapter 1 practice program 8
// Found on page 37
// Calculates the value of a given number of coins

#include <iostream>

int val(short,short,short,short);

int main()
{
    // Set up some variables
    short q;    // Quarters
    short d;    // Dimes
    short n;    // Nickles
    short p;    // Pennies

    // Get user input
    std::cout << "This program will calculate cash value of a given number of coins." << std::endl << std::endl;
    std::cout << "Number of quarters: " << std::endl;
    std::cin >> q;
    std::cout << "\nNumber of dimes: " << std::endl;
    std::cin >> d;
    std::cout << "\nNumber of nickels: " << std::endl;
    std::cin >> n;
    std::cout << "\nNumber of pennies: " << std::endl;
    std::cin >> p;

    // Display this info for the user
    std::cout << "\nThe calculated value of this set of coins is " << val(p,n,d,q) << " cents." << std::endl;
    
    return 0;
}

// Calculate the value of the coins
int val(short pen, short nic, short dim, short qua)
{
    return ( pen + (nic * 5) + (dim * 10) + (qua * 25));
}

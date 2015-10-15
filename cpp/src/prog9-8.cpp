// Program 9-8
// This program displays the memory address of individual array elements

#include <iostream>
#include <iomanip>

int main()
{
    const int NUM_COINS = 5;
    double coins[NUM_COINS] = {0.05, 0.1, 0.25, 0.5, 1.0};
    double *doublePtr;  // Pointer to a double
    int count;          // Array index

    // Use the pointer to display the values in the array
    std::cout << "Here are the values in the coins array: \n";
    for(count = 0; count < NUM_COINS; count++)
    {
        // Get the address of an array element
        doublePtr = &coins[count];

        // Display the content of that element
        std::cout << *doublePtr << " ";
    }
    std::cout << std::endl;
    return 0;
}

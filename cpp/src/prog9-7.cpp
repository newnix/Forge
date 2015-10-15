// Practice Program 9-7
// Displays the relationship between pointers and arrays
// Uses subscript notation with a pointer variable 
// and uses pointer notation with an array name

#include <iostream>

int main()
{
    const int NUM_COINS = 5;
    double coins[NUM_COINS] = {0.05, 0.1, 0.25, 0.5, 1.0};
    double *doublePtr;  // Pointer to a double
    int count;          // Array index

    // Assign the address of the couns array to doublePtr
    doublePtr = coins;

    // Display the contents of the coins array
    // Using subscripts with the pointer
    std::cout << "Here are the values in the coins array: \n";
    for(count = 0; count < NUM_COINS; count++)
        std::cout << doublePtr[count] << " ";

    // Display the contents of the coins array
    // This time using pointer notation
    std::cout << "\n And here they are again: \n";
    for(count = 0; count < NUM_COINS; count++)
        std::cout << *(coins + count) << " ";
    std::cout << std::endl;

    return 0;
}

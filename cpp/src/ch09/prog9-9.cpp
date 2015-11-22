// Practice Program 9-9
// This program usues a pointer to display the contents of an array

#include <iostream>

int main ()
{
    const int SIZE = 8;
    int set[SIZE] = {5, 10, 15, 20, 25, 30, 35, 40};
    int *numPtr;    // Pointer
    int count;      // Counter var for loops

    // Make numPtr point to the set array
    numPtr = set;

    // Use the pointer to display the array contents
    std::cout << "The numbers in this set are: \n";
    for(count = 0; count < SIZE; count++)
    {
        std::cout << *numPtr << " ";
        numPtr++;
    }

    // Display the array contents in reverse order
    std::cout << "\nThe number set in reverse order are: \n";
    for(count = 0; count < SIZE; count++)
    {
        numPtr--;
        std::cout << *numPtr << " ";
    }

    return 0;
}

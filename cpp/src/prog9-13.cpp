// Practice Program 9-13
// Demonstrates a pointer to a const parameter

#include <iostream>

void displayValues(const int *, int);

int main()
{
    // Array sizes
    const int SIZE = 6;

    // Define an array of const ints
    const int array1[SIZE] = { 1, 2, 3, 4, 5, 6};

    // Define an array of nonconst ints
    int array2[SIZE] = { 7, 8, 9, 10, 11, 12 };

    // Display the contents of the const array
    displayValues(array1, SIZE);

    // Display the contents of the nonconst array
    displayValues(array2, SIZE);

    return 0;
}

// The display Values function uses a pointer to prarameter to display the contents of an array

void displayValues(const int *numbers, int size)
{
    // Display all the values
    for (int count = 0; count < size; count++)
    {
        std::cout << *(numbers + count) << " ";
    }
    std::cout << std::endl;
}

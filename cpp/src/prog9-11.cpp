// Practice Program 9-11
// Using pointers as function parameters

#include <iostream>

// Function Prototypes
void getNumber(int *);
void doubleValue(int *);

int main()
{
    int number;

    // Call getNumber and pass the address of the number
    getNumber(&number);

    // Call doubleValue and pass the address of the number
    doubleValue(&number);

    // Display the value in number
    std::cout << "That value doubled is " << number << std::endl;
    return 0;
}

// Definitionof getNumber. The parameter, input, is a pointer.
// This function asks the user for a number.
// The value entered is stored in the variable pointed to by input

void getNumber(int *input)
{
    std::cout << "Enter an integer: ";
    std::cin >> *input;
}

// Definition of doubleValue. The parameter, value is a pointer
// This function multiplies the variable pointed to by 2

void doubleValue(int *input)
{
    *input *= 2;
}

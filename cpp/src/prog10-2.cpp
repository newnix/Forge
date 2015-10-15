// Practice program 10-2
// Practical application of the functions used in 10-1

#include <iostream>
#include <cctype>

// Prototype of the function about to be used
bool testNum(char [], int);

int main()
{
    const int SIZE = 8; //Array size
    char customer[SIZE];    // To hold the customers' number

    // Get the customer number
    std::cout << "Enter a customer number in the form ";
    std::cout << "LLLNNNN\n";
    std::cout << "(LLL = letters and NNNN = numbers): ";
    std::cin.getline(customer, SIZE);

    // Determine if the input is valid
    if (testNum(customer, SIZE))
        std::cout << "That's a valid customer number. \n";
    else
    {
        std::cout << "That's not a valid customer number, ";
        std::cout << "please use the correct format of LLLNNNN.\n";
        std::cout << "EX: ABC1234\n";
    }

    return 0;
}

// Definition of the testNum function
// Determines if the number given fits the proper format

bool testNum(char custNum[], int size)
{
    int count; //loop counter

    // Test the first three characters to ensure they're letters
    for (count = 0; count < 3; count ++)
    {
        if (!isalpha(custNum[count]))
            return false;
    }

    // Test the final four characters for numerical values
    for (count = 3; count < size - 1; count ++)
    {
        if (!isdigit(custNum[count]))
            return false;
    }
    return true;

}


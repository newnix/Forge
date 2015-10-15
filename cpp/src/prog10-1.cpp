// Example program from Chapter 10
// Demonstrates some char testing functions

#include <iostream>
#include <cctype>

int main()
{
    char input;

    std::cout << "Enter any character: ";
    std::cin.get(input);
    std::cout << "The character you entered is: " << input << std::endl;
    
    if (isalpha(input))
        std::cout << "That's an alphabetic character."<< std::endl;
    if (isdigit(input))
        std::cout << "That's a numeric digit." << std::endl;
    if (islower(input))
        std::cout << "That's a lower case character." << std::endl;
    if (isupper(input))
        std::cout << "That's an upper case character." << std::endl;
    if (isspace(input))
        std::cout << "That's a space character." << std::endl;

    return 0;
}


// Practice program 10-5
// Found on p.551
// Practices using the concept of C-strings

#include <iostream>

int main()
{
    const int SIZE = 80;
    char line[SIZE];    // Holds a line of input
    int count = 0;      // Loop counter

    // Get a line of input
    std::cout << "Enter a sentence of no more than " << (SIZE-1) << " characters: " << std::endl;
    std::cin.getline(line, SIZE);

    // Display the input one character at a time
    std::cout << "The sentence you entered is: " << std::endl;
    while (line[count] != '\0')
    {
        std::cout << line[count];
        count ++;
    }std::cout << std::endl;
    return 0;
}

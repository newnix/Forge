// Program 9-1 
// This program practices the method used for returning the memory address of a variable

#include <iostream>

int main()
{
    int x = 25;

    std::cout << "The memory address of 'x' is: " << &x << std::endl;
    std::cout << "The size of 'x' is: " << sizeof(x) << " bytes\n";
    std::cout << "The value of 'x' is: " << x << std::endl;

    return 0;
}

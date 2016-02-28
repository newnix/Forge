// Practice Program 9-4
// This Program works with pointers storing different variable types

#include <iostream>

int main()
{
    int x = 25, y = 50, z = 75;     // Three ints
    int *ptr;                       // Pointer value

    // Display the contents of x, y, and z
    std::cout << "Here are the values of x, y, and z: " << std::endl;
    std::cout << "The value of x: " << x << std::endl;
    std::cout << "The value of y: " << y << std::endl;
    std::cout << "The value of z: " << z << std::endl;

    // Use the pointer to manipulate these variables
    ptr = &x;   // Store the address of x in ptr
    *ptr += 100;    // Add 100 to the var 'x'

    ptr = &y;   // Store the address of y in ptr
    *ptr += 100;    // Add 100 to the var 'y'

    ptr = &z;   // Store the address of z in ptr
    *ptr += 100;    // Add 100 to the var 'z'

    // Display the contents of x, y, and z again
    std::cout << "\nHere are the values of x, y, and z: " << std::endl;
    std::cout << "The value of x: " << x << std::endl;
    std::cout << "The value of y: " << y << std::endl;
    std::cout << "The value of z: " << z << std::endl;

    return 0;
}

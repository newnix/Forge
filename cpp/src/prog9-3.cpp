// Practice Program 9-3
// This program deals with the indirection operator
// This allows us to indirectly manipulate variables

#include <iostream>

int main()
{
    int x = 25;     // int var
    int *ptr;       // pointer var, can store ints

    ptr = &x;       // store the memory address of 'x' in ptr

    // Use both 'x' and ptr to display the value stored in 'x'
    std::cout << "Here is the value in 'x' printed twice: \n";
    std::cout << "Called directly: " << x << std::endl;              // Displays the value in 'x'
    std::cout << "Called through pointer: " << *ptr << std::endl;    // Displays the value in 'x', indirectly

    // Assign 100 to the location pointed to by ptr.
    // This will change the value of 'x' too
    *ptr = 100;

    // Use both 'x' and ptr to display the contents of 'x'
    std::cout << "\nHere's the value in 'x' printed twice: \n";
    std::cout << "Called directly: " << x << std::endl;
    std::cout << "Called through pointer: " << *ptr << std::endl;

    return 0;
}

// Practice program working with pointers
// Practice program 9-2

#include <iostream>

int main()
{
    int x = 25;     // int var
    int *ptr;       // pointer var, can point to an int

    ptr = &x;       // stores the address of 'x' in ptr
    std::cout << "The value in 'x' is: " << x << std::endl;
    std::cout << "The address of 'x' is: " << ptr << std::endl;
    return 0;
}

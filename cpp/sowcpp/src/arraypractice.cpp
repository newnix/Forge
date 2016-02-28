// Practice using arrays
// Using the example found on p.381

#include <iostream>

int main()
{
    const int NUM_EMPLOYEES = 6;
    int hours[NUM_EMPLOYEES];

    // Get the hours worked by each employee

    std::cout << "Enter the number of hours worked by "
              << NUM_EMPLOYEES << " employees,one at a time: ";
    std::cin >> hours[0];
    std::cin >> hours[1];
    std::cin >> hours[2];
    std::cin >> hours[3];
    std::cin >> hours[4];
    std::cin >> hours[5];

    // Display the values in the array
    std::cout << " " << hours[0];
    std::cout << " " << hours[1];
    std::cout << " " << hours[2];
    std::cout << " " << hours[3];
    std::cout << " " << hours[4];
    std::cout << " " << hours[5];
    std::cout << std::endl;
    return 0;
}

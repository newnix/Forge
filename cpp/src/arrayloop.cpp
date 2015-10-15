// Array loop practice
// Using the example found on p.383

#include <iostream>

int main()
{
    const int NUM_EMPLOYEES = 6; // Number of Employees
    int hours[NUM_EMPLOYEES];   //Each Employee's hours
    int count;  // Loop counter

    // Input the numbers worked
    for(count = 0; count < NUM_EMPLOYEES; count++)
    {
        std::cout << "Enter the hours worked by employee "
            << (count + 1) << ": ";
        std::cin >> hours[count];
    }

    // Dispaly the contents of the array
    std::cout << "The hours you entered are: ";
    for (count = 0; count < NUM_EMPLOYEES; count++)
        std::cout << " " << hours[count];
    std::cout<< std::endl;
    return 0;
}

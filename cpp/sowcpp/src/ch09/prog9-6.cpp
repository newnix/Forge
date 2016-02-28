// Program 9-6
// Practice using arrays with pointer notation

#include <iostream>

int main()
{
    const int SIZE = 5;     // Size of the array
    int numbers[SIZE];      // Array of ints
    int count;              // Counter var

    // Get values to store in the array
    // Use pointer notation instead of subscripts
    std::cout << "Enter " << SIZE << " numbers: ";
    for(count = 0; count < SIZE; count++)
    {
        std::cin >> *(numbers + count);
    }

    // Display the values in the array
    // Using pointer notation instead of subscripts
    std::cout << "\nHere are the numbers you entered: \n";
    for(count = 0; count < SIZE; count++)
        std::cout << *(numbers + count) << " ";
    std::cout << std::endl;

    return 0;
}

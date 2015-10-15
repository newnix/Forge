// Practice Program 9-10
// Displays the difference between pointer addresses and pointer references

#include <iostream>

int main()
{
    int set[8] = {5, 10, 15, 20, 25, 30, 35, 40};
    int *nums = set;    // Make nums point to a set

    // Display the number in the array
    std::cout << "The numbers in set are:\n";
    std::cout << *nums << " ";  // Display the first element

    while (nums < &set[7])
    {
        // Advance nums to point to the next element
        nums++;
        // Display the value pointed to by nums
        std::cout << *nums << " ";
    }

    // Display the numers in reverse order
    std::cout << "\nThe numbers in set backwards are: \n";
    std::cout << *nums << " ";

    while (nums > set)
    {
        // Move backwards to the previous element
        nums--;
        // Display the value pointed to by nums
        std::cout << *nums << " ";
    }
    return 0;
}

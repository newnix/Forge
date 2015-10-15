// Practice Program 9-15
// This program demonstrates a function that returns a pointer

#include <iostream>
#include <cstdlib>      // For the rand and srand calls
#include <ctime>        // For the time function

// Function prototype
int *getRandomNumbers(int);

int main()
{
    int *numbers;   // To point to the numbers

    // Get an array of five random numbers
    numbers = getRandomNumbers(5);

    // Display the numbers
    for (int count =0; count < 5; count ++)
        std::cout << numbers[count] << std::endl;

    // Free the memory
    delete [] numbers;
    numbers = 0;
    return 0;
}

// The getRandomNumbers function returns a point to an array of random ints
// The parameter indicates the number of numbers requested

int *getRandomNumbers(int num)
{
    int *arr;       // Array to hold the numbers

    // Return null if the num is zero or negative
    if (num <= 0)
        return NULL;

    // Dynamically allocate the array
    arr = new int[num];

    // Seed the random number generator by passing the return value of time to srand
    srand( time(0));

    // Populate the array with random numbers
    for (int count = 0; count < num; count ++)
        arr[count] = rand();

    // Return a pointer to the array
    return arr;
}

// Assignment 2, Page 539, Movie stats Pseudocode

#include <iostream>

double median(int *, int);
double mean(int *, int);
int mode(int*, int);
int *makeArray(int);
void getMovieData(int *, int);
void selectionSort(int [], int);

int main()
{
    Ask user for number of students surveyed;
    store the value in an int called students;

    create an array with the number of students used as the numer of addresses
    accept input for each index of the array

    use the selectionSort function to sort the values given

    run the statistical calculations for average, medain, and mode on the array

    print the results of the statistical functions to stdout.

}

int *makeArray(int arrayAddresses)
{
    create a pointer to hold the array

    ensure all inputs are greater than zero

    return the array pointer with the array addresses created
}

int getMovieData(int *arrayptr, int counter)
{
    create a for loop to allow input to the array addresses

    return the array

}

double mean (int *arrayptr, int arraySize)
{
    use a for loop to add all the values in the array together

    divide the sum of the values by the arraySize

    return the result of the above operation
}

double median (int *arrayptr, int size)
{
    ensure the array has been sorted

    determine if there's an odd or even number of values in the array

    locate the median, or calculate the average of the two values in the middle

    return the median value
}

int mode(int *arrayptr, int count)
{
    check the values in the array to determine if there are any repeat values

    determine which value stored in the array is repeated the most

    return the most frequently repeated value
}


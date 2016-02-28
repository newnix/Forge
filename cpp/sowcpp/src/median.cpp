// Program written as an example of how to find the median
// Using an example fount on xoax.net
// written 2015.09.18 at 20:08

#include <iostream>

double median(int *, int);

int main()
{
    int array[5] = { 1, 2, 3, 4, 5};

    std::cout << "The median of the pre-sorted array is: " << median(array, 5) << std::endl;
    return 0;
}

double median (int *arr, int size)
{
    double median = 0.0;
    if ((size % 2) == 0)
    {
        median = (arr[size/2] + arr[(size/2) - 1]) / 2.0;
    }
    else
    {
        median = arr[size/2];
    }
    delete [] arr;
    return median;
}


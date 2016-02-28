// Practice Program 9-12
// This program allows for pointers to create array addresses

#include <iostream>
#include <iomanip>

// Function Prototypes
void getSales(double *, int);
double totalSales(double *, int);

int main()
{
    const int QTRS = 4;
    double sales[QTRS];

    // Get the sales data for all quarters
    getSales(sales, QTRS);

    // Set the numeric output formatting
    std::cout << std::fixed << std::showpoint << std::setprecision(2);

    // Display the total sales for the year
    std::cout << "The total sales for the year are $";
    std::cout << totalSales(sales,QTRS) << std::endl;

    return 0;
}

// Definition of getSales
// This function uses a poinnter to accept the address of an array to doubles
// Also asks the user to enter sales figures and stores them in the array
void getSales(double *arr, int size)
{
    for (int count = 0; count < size; count ++)
    {
        std::cout << "Enter the sales figure for quarter ";
        std::cout << (count + 1) << ": ";
        std::cin >> arr[count];
    }
}

// Definition of totalSales
// This function uses a pointer to accept the address of an array
// The function returns the total of the elements in the array
double totalSales(double *arr, int size)
{
    double sum = 0.0;

    for (int count = 0; count < size; count ++)
    {
        sum += *arr;
        arr++;
    }
    return sum;
}

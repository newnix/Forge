// Practice Program 9-14
// This program finds totals and averages for any 2 related sets of data
// EX: sales over a given number of days

#include <iostream>
#include <iomanip>

int main()
{
    double *sales,      // To dynamically allocate an array
        total = 0.0,    // Accumulator
        average;        // To hold average sales
    int numDays,        // To hold the number of days of sales
        count;          // Counter variable

    // Get the number of days of sales
    std::cout << "How many days of sales figures do you wish to process? ";
    std::cin >> numDays;

    // Dynamically allocate an array large enough to hold
    // the number of days of sales figures
    sales = new double[numDays];

    // Get the sales figures for each day
    std::cout << "Enter the sales figures below: \n";
    for (count = 0; count < numDays; count ++)
    {
        std::cout << "Day " << (count + 1) << ": ";
        std::cin >> sales[count];
    }

    // Calculate the total sales
    for (count = 0; count < numDays; count++)
    {
        total += sales[count];
    }

    // Calculate the average sales per day
    average = total / numDays;

    // Display the results
    std::cout << std::fixed << std::showpoint << std::setprecision(2);
    std::cout << "\n\nTotal Sales: $" << total << std::endl;
    std::cout << "\n\nAverage Sales: $" << average << std::endl;

    // Free dynamically allocated memory
    delete [] sales;
    sales = 0;      // Make sales point to null

    return 0;
}

// Practice program 11-11 on page 630
// Demonstrates the use of enumerated data types
#include <iostream>
#include <iomanip>
using namespace std;

enum day { monday, tuesday, wednesday, thursday, friday };

int main()
{
    const int NUM_DAYS = 5;     // The number of days
    double sales[NUM_DAYS];     // Array to hold sales each day
    double total = 0.0;         // Accumulator
    int index;                  // Loop counter

    // Get the sales for each day
    for (index = monday; index <= friday; index ++)
    {
        cout << "Enter the sales for day " << index << ": ";
        cin >> sales[index];
    }

    // Calculate the total sales
    for (index = monday; index <= friday; index ++ )
    {
        total += sales[index];
    }

    // Display the total
    cout << "The total sales are $" << setprecision(2) << fixed << total << endl;

    return 0;
}

// Practice program 11-12 on page 632
// Basically the same as 11-11, but with casting the enumerated values into an int
#include <iostream>
#include <iomanip>
using namespace std;

enum day { monday, tuesday, wednesday, thursday, friday, saturday, sunday };

int main()
{
    const int NUM_DAYS = 7;     // Number of days
    double sales[NUM_DAYS];     // To hold the sales of each day
    double total = 0.0;         // Accumulator
    day workday;                // Loop counter

    // Get the sales for each day
    for (workday = monday; workday <= sunday; workday = static_cast<day>(workday + 1))
    {
        cout << "Enter the sales for day " << workday << ": ";
        cin >> sales[workday];
    }

    // Calculate the total sales
    for (workday = monday; workday <= sunday; workday = static_cast<day>(workday + 1))
    {
        total += sales[workday];
    }

    // Display the total
    cout << "The total sales are $" << setprecision(2) << fixed << total << endl;

    return 0;
}

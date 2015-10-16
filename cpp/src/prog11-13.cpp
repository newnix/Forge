// Practice program 11-13 on page 634
// This is the same as 11-11 and 11-12, but now the days are actually printed on the output
#include <iostream>
#include <iomanip>
using namespace std;

enum day { monday, tuesday, wednesday, thursday, friday, saturday, sunday };

// Function prototype
void displayday(day);

int main()
{
    const int NUM_DAYS = 7;         // Days in a week
    double sales[NUM_DAYS];         // Sales for each day
    double total = 0.0;             // Accumulator
    day workday;                    // Loop counter

    // Get the sales for each day
    for (workday = monday; workday <= sunday; workday = static_cast<day>(workday + 1))
    {
        cout << "Enter the sales for day ";
        displayday(workday);
        cout << ": ";
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

/*
 * Definition of the displayday(day) function.
 * This function accepts the day argument and prints the name of the day to stdout
 */

void displayday(day d)
{
    switch(d)
    {
        case monday : cout << "Monday";
                      break;
        case tuesday : cout << "Tuesday";
                      break;
        case wednesday : cout << "Wednesday";
                      break;
        case thursday : cout << "Thursday";
                      break;
        case friday : cout << "Friday";
                      break;
        case saturday : cout << "Saturday";
                      break;
        case sunday : cout << "Sunday";
                      break;
    }
}

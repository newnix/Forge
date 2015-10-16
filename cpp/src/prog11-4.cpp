// Practice Program 11-4 found on page 606
// Exemplifies mixing arrays and data structures
#include <iostream>
#include <iomanip>
using namespace std;

struct payInfo
{
    int hours;      // Hours worked
    double payRate; // Hourly pay rate
};

int main()
{
    const int NUM_WORKERS = 3;      // Number of workers
    payInfo workers[NUM_WORKERS];   // Array of structures
    int index;                      // Loop counter

    // Get employee pay data
    cout << "Enter the hours worked by " << NUM_WORKERS
         << " employees and their hourly rates.\n";

    for (index = 0; index < NUM_WORKERS; index ++)
    {
        // Get the hours worked by an employee
        cout << "Hours worked by employee #" ;
        cout << (index + 1) << ": ";
        cin >> workers[index].hours;
        cout << endl;
    }

    for (index = 0; index < NUM_WORKERS; index ++)
    {
        // Get the hourly wage for each worker
        cout << "Hourly wage for employee #:";
        cout << (index + 1) << ": ";
        cin >> workers[index].payRate;
        cout << endl;
     }

    // Display each employee's gross pay
    cout << "Here's the gross pay for each employee:\n";
    cout << fixed << showpoint << setprecision(2);
    for (index = 0; index < NUM_WORKERS; index ++)
    {
        double gross;
        gross = workers[index].hours * workers[index].payRate;
        cout << "Employee #" << (index + 1);
        cout << ": $" << gross << endl;
    }

    return 0;
}

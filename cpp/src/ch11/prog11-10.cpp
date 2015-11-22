// Practice program 11-10 found on page 624
// This program demonstrates the use of union data structures
// This program is the same as 11-9, but with an anonymous union
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

int main()
{
    union
    {
        int hours;  // Hours worked
        double sales;   // Amount of sales
    };

    char paytype;           // Hold the pay type
    float payrate;          // Hourly pay rate
    float grosspay;         // Gross pay

    cout << fixed << showpoint << setprecision(2);
    cout << "This program calculates either hourly wage or commission.\n";

    // Get the pay type, hourly or commission
    cout << "Enter H for hourly wages or C for commision: ";
    cin >> paytype;
    
    // Determine if the pay type is hourly or commission
    if (toupper(paytype) == 'H')
    {
        // This is an hourly paid employee
        // Get the rate and hours worked
        cout << "What is the hourly pay rate? ";
        cin >> payrate;
        cout << "How many hours were worked?";
        cin >> hours;

        // Calculate the gross pay
        grosspay = hours * payrate;
        cout << "Gross pay: $" << grosspay << endl;
    }

    else if (toupper(paytype) == 'C')
    {
        // This is a commissioned employee
        // We need to get the amount of sales
        cout << "What are the total sales for this employee? ";
        cin >> sales;

        // Calculate the gross pay
        grosspay = sales * 0.10;
        cout << "Gross pay: $" << grosspay <<endl;
    }

    else
    {
        // The user made an invalid choice
        cout << paytype << " is not a valid selection.\n";
    }
    
    return 0;
}

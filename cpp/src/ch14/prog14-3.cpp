// Practice program 14-3 on page 805
// This program demonstrates the use of a static member function

#include <iomanip>
#include <iostream>
#include "budgetv2.h"

using namespace std;

int main()
{
    int count;  // Loop counter
    double mainOfficeRequest;   // Main office budget request
    const int NUM_DIVISIONS = 4;    // Number of divisions

    // Get the main office's budget request
    // Note that no instances of the BUdget class have been defined
    cout << "Enter the main office's budget request: ";
    cin >> mainOfficeRequest;
    Budget::mainOffice(mainOfficeRequest);

    Budget divisions[NUM_DIVISIONS];    // An array of the Budget objects

    // Get the budget requests for each division
    for ( count = 0; count < NUM_DIVISIONS; count++)
    {
        double budgetAmt;
        cout << "\nEnter the budget requset for division ";
        cout << (count + 1) << ": ";
        cin >> budgetAmt;
        divisions[count].addBudget(budgetAmt);
    }

    // Display the budget requests and the corporate budget
    cout << "\nHere are the division budget requests: \n";
    for (count = 0; count < NUM_DIVISIONS; count ++)
    {
        cout << fixed << setprecision(2);
        cout << "\tDivision " << ( count + 1 ) << "\t$ ";
        cout << divisions[count].getDivBudget() << endl;
    }

    cout << "\tTotal Budget Requests:\t$ ";
    cout << divisions[0].getCorpBudget() << endl;

    return 0;
}

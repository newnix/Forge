// This program demonstrates a static class member variable
// Practice Program 14-2 on page 803

#include <iostream>
#include <iomanip>
#include "budgetv1.h"

using namespace std;

int main()
{
    int count;                          // Loop counter
    const int NUM_DIVISIONS = 4;        // Number of divisions
    Budget divisions[NUM_DIVISIONS];    // Array of budget objects

    // Get the budget requests from each division
    for ( count = 0; count < NUM_DIVISIONS; count ++ )
    {
        double budgetAmount;
        cout << "Enter the budget request for division " << (count + 1) << " :" ;
        cin >> budgetAmount;
        divisions[count].addBudget(budgetAmount);
    }

    // Display the budget requests and the corporate budget

    cout << fixed << setprecision(2);
    cout << "\nHere are the division budget requests:\n";
    for ( count = 0; count < NUM_DIVISIONS; count ++ )
    {
        cout << "\tDivision " << (count + 1) << "\t$ ";
        cout << divisions[count].getDivisionBudget() << endl;
    }

    cout << "\tTotal Budget Requests:\t$ ";
    cout << divisions[0].getCorpBudget() << endl;

    return 0;
}

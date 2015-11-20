// Practice program 14-4
// Found on page 810
// This demonstrates the use of a static member function 
// And implements a friend function as well.

#include <iostream>
#include <iomanip>
#include "budgetv3.h"

using namespace std;

double Budget::corpBudget = 0; // Declaring a definition and initial value in the global scope

int main()
{
    int count;      // Loop counter
    double mainOfficeReq;   // Main office budget request
    const int NUM_DIVISIONS = 4;    // Number of divisions

    // Get the main office's budget request
    cout << "Enter the main office's budget request: ";
    cin >> mainOfficeReq;
    Budget::mainOffice(mainOfficeReq);

    Budget divisions[NUM_DIVISIONS];    // Array of budgets
    auxOffice auxOffices[4];            // Array of auxOffices

    // Get the budget requests for each division
    // And their auxillary offices
    for (count = 0; count < NUM_DIVISIONS; count++)
    {
        double budgetAmt;   // Holds the budget

        // Get the request for the division office
        cout << "Enter the budget request for division ";
        cout << (count + 1) << ": ";
        cin >> budgetAmt;
        divisions[count].addBudget(budgetAmt);

        // Get the request for the auxillary office.
        cout << "Enter the budget request for that division's Auxillary Office: ";
        cin >> budgetAmt;
        auxOffices[count].addBudget(budgetAmt, divisions[count]);
    }

    // Display the budget requests
    cout << fixed << setprecision(2);
    cout << "\nHere are the division budget requests:\n";
    for (count = 0; count < NUM_DIVISIONS; count++)
    {
        cout << "\tDivision " << (count+1) << "\t$";
        cout << divisions[count].getDivBudget() << endl;
        cout << "\tAuxillary office:\t$";
        cout << auxOffices[count].getDivBudget() << endl << endl;
    }

    // Display the total requests
    cout << "Total Budget Requests:\t$";
    cout << divisions[0].getCorpBudget() << endl;
    return 0;
}

// Third version of the Budget header file
// Found on page 807

#ifndef BUDGET_H    // Check for the existence of the header program
#define BUDGET_H    // Define the Budget class

#include "auxil.h"  // Include the "auxil" header file 

// Declare Budget class

class Budget
{
    private:
        static double corpBudget;   // Static member var
        double divBudget;           // Instance member var

    public: 
        Budget()
            { divBudget =  0; }     // generic constructor

        void addBudget(double b)
            { divBudget += b; corpBudget += b; } // Add 'b' to both budgets

        double getDivBudget() const
            { return divBudget; }   // Return the division's budget

        double getCorpBudget() const
            { return corpBudget; }  // Return the corporation budget

        // Static member function
        static void mainOffice(double);

        // Friend function
        friend void auxOffice::addBudget(double, Budget &);
};

#endif

// Practice header for budgeting, version 1
// Found on page 802

#ifndef BUDGET_H
#define BUDGET_H

// Budget class declaration
class Budget
{
    private:
        static double corpBudget;   // Static member
        double divisionBudget;      // Instance member
    public:
        Budget()
            { divisionBudget = 0; }
        void addBudget(double b)    // Add each budget request to the static var corpBudget
            { divisionBudget += b; corpBudget += b; }
        double getDivisionBudget() const    // Returns the budget request for a given division
            { return divisionBudget; }
        double getCorpBudget() const    // Return the static var
            { return corpBudget; }
};

// Definition of static member variable corpBudget
double Budget::corpBudget = 0;

#endif

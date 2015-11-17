// This is the second version of the budget header
// Found on page 804

#ifndef BUDGET_H    // Make sure there's not already an instance of this header loaded
#define BUDGET_H    // Load the header file into the project file

// Define the budget class
class Budget
{
    private:
        static double corpBudget;   // Static member var
        double divBudget;           // Instance member var

    public:
        Budget()
            { divBudget = 0; }  // Constructor

        void addBudget(double b)
            { divBudget += b; corpBudget += b; }    // Add the budget amount 'b' to both vars

        double getDivBudget() const
            { return divBudget; }   // Return the divisions budget

        double getCorpBudget() const
            { return corpBudget; }  // Return the corporate budget

        static void mainOffice(double); // Static member function
};

// mainOffice(double) is meant to be defined in the budget program.
// In this case, budget.cpp or prog14-3
// Adding the definitions used in budget.cpp

// Definition of corpBudget
double Budget::corpBudget = 0;

/*
 * Definition of the function mainOffice
 * This adds the main office's budget to the corpBudget var.
 */

void Budget::mainOffice(double moffice)
{
    corpBudget += moffice;
}

#endif

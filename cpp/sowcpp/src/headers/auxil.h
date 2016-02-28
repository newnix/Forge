// Auxil.h file found on page 808
// Accompanies budgetv3.h

#ifndef AUXIL_H     // Check for the header file being used elswhere
#define AUXIL_H     // Load the contents of the header file

class Budget;       // Forward declaration of the Budget class

// Aux class declaration

class auxOffice
{
    private:
        double auxBudget;

    public:
        auxOffice()
            { auxBudget = 0; }  // Constructor for the class

        double getDivBudget() const
            { return auxBudget; }   // Return the budget for the aux office

        void addBudget(double, Budget &);
};

#endif


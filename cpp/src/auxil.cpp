// The auxil.cpp source file. 
// Meant to accompany the auxil.h file
// Found on page 809
#include "auxil.h"
#include "budgetv3.h"

/*
 * Definition of the function auxOffice.
 * This function is declared a friend by the Budget class.
 * It adds the value of the argument, 'b' to the static corpBudget.
 */

void auxOffice::addBudget(double b, Budget &div)
{
    auxBudget += b;
    div.corpBudget += b;
}

/*
 * Adding a definition to the function mainOffice since one isn't included in the book
 * Will simlpy add the value 'b' to the corpBudget static var.
 */

void Budget::mainOffice(double b)
{
    corpBudget += b;
}

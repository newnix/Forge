// Practice program to accompany budgetv2.h
// found on page 805

#include "budgetv2.h"

// Definition of corpBudget static member variable
double Budget::corpBudget = 0;

/*
 * Definition of the function mainOffice.
 * This adds the main office's budget request to the corpBudget var.
 */

void Budget::mainOffice(double moffice)
{
    corpBudget += moffice;
}

// CsStudent.cpp, holds the function getRemainingHours()
// found on page 924

#include <iostream>
#include "csStudent.h"

using namespace std;

/*
 * The csStudent::getRemainingHours() function returns
 * the number of hours left to be taken
 */

int csStudent::getRemainingHours() const
{
    int reqHours,   // Hours required
    remainingHours; // Hours left to be completed

    // Calculate the required hours
    reqHours = MATH_HOURS + CS_HOURS + GEN_ED_HOURS;

    // Calculate the remaining hours
    remainingHours = reqHours - (mathHours + csHours + genEdHours);

    // return the remaining hours
    return remainingHours;
}

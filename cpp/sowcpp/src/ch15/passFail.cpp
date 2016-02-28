// Companion file for passfail.h

#include "passFail.h"

/*
 * Member function passFail::getLetter()
 * Returns 'P' if passing and 'F' if failing.
 */

char passFail::getLetter() const
{
    char letterG;   // Placeholder for the letter grade

    if (score >= minPassingScore)
    {
        letterG = 'P';
    }

    else
    {
        letterG = 'F';
    }

    return letterG;
}

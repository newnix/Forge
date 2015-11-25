// Graded activity version 1 source file
// Found on page 871

#include "gradedActivityv1.h"

/*
 * Member function gradedActivity::getLetter
 */

char gradedActivity::getLetter() const
{
    char letterGrade;   // Holds the letter grade

    if (score > 89)
    {
        letterGrade = 'A';
    }
    else if (score > 79)
    {
        letterGrade = 'B';
    }
    else if (score > 69)
    {
        letterGrade = 'C';
    }
    else if (score > 59)
    {
        letterGrade = 'D';
    }
    else
    {
        letterGrade = 'F';
    }

    return letterGrade;
}

// PassFailExam companion source file
// found on page 904

#include "passFailExam.h"

/*
 * Define the set function
 * The parameters are the number of questions and the number of questions missed
 */

void passFailExam::set(int questions, int nmissed)
{
    double numericScore;    // To hold the numeric score

    // Set the number of questions and number missed
    numQ = questions;
    missed = nmissed;

    // Calculate the points for each question
    points = (100.0 / numQ);

    // Calculate the numeric score for this exam
    numericScore = 100.0 - (points * missed);

    // Call the inhereted setScore function to set the numeric score
    setScore(numericScore);
};

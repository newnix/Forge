// Final exam source file
// Includes some member functions for the finalExam class

#include "finalExam.h"

/*
 * set function
 * The parameters are the number of questions
 * and the number of questions missed.
 */

void finalExam::set(int nquestions, int nmissed)
{
    double numScore;    // Holds the numeric score

    // Set the number of questions and number missed
    numQ = nquestions;
    missed = nmissed;

    // Calculate the points for each question
    points = 100.0/numQ;

    // Calculate the score for the exam
    numScore = 100.0 - ( missed * points );

    // Call the inhereted setScore function to set the numeric score
    setScore(numScore);
}

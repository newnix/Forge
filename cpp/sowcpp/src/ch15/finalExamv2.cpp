// Second version of the finalExam program
// found on page 880

#include "finalExamv2.h"

/*
 * The set function definition
 * parameters are the number of questions and the questions missed
 */

void finalExam::set(int nquestions, int nmissed)
{
    double numScore;    // To hold the numeric value

    // Set the number of questions and number missed
    numQ = nquestions;
    missed = nmissed;

    // Calculate the points for each question
    points = 100.0 / numQ;

    // Calculate the score for this exam
    score = 100.0 - (missed * points);

    // The the inherited  setScore function to set the numeric score
    setScore(score);

    // Call the adjustScore function to adjust the score
    adjustScore();
}

/*
 * Definition of test::adjustScore.
 * If the score is within 0.5 points of the next whole point,
 * it rounds the score up and recalculates the letter grade
 */

void finalExam::adjustScore()
{
    double fraction = score - static_cast<int>(score);

    if(fraction >= 0.5)
    {
        // Adjust the score variable in the gradedActivity class
        score += (1.0 - fraction);
    }

}

char gradedActivity::getLetter() const
{
    if (score > 89)
    {
        return 'A';
    }
    else if (score > 79)
    {
        return 'B';
    }
    else if (score > 69)
    {
        return 'C';
    }
    else if (score > 59)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

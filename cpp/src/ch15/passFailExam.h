// Pass/Fail exam header file
// found on page 903

// Header guard and inclusions
#ifndef PASSFAILEXAM_H
#define PASSFAILEXAM_H

#include "passFail.h"

class passFailExam : public passFail
{
    private:
        int numQ;        // Number of questions
        double points;  // Points per question
        int missed;     // Questions missed

    public:
        // Default constructor
        passFailExam() : passFail()
        {
            numQ = 0;
            points = 0.0;
            missed = 0;
        }

        // Constructor with arguments
        passFailExam(int questions, int nmissed, double mps) : passFail(mps)
        {
            set(questions, nmissed);
        }

        // Mutator function
        void set(int, int); // Defined in the accompanying source file

        // Accessor functions
        double getNumQ() const
        {
            return numQ;
        }

        double getPoints() const
        {
            return points;
        }

        int getMissed() const
        {
            return missed;
        }
};
#endif

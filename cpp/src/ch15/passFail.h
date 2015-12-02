// Header file describing a pass/fail activity
// found on page 902

// Header guards
#ifndef PASSFAIL_H
#define PASSFAIL_H

#include "gradedActivityv3.h"

class passFail : public gradedActivity
{
    protected:
        double minPassingScore; // Minimum passing score for the activity
    public:
        // Default constructor
        passFail() : gradedActivity()
        {
            minPassingScore = 0.0;
        }

        // Constructor
        passFail(double mps) : gradedActivity()
        {
            minPassingScore = mps;
        }

        // Mutator
        void setMinPassingScore(double mps)
        {
            minPassingScore = mps;
        }

        // Accessors
        double getMinPassingScore() const
        {
            return minPassingScore;
        }

        virtual char getLetter() const;
};
#endif

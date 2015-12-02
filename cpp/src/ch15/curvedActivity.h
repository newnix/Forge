// Curved Activity header file
// found on page 897
// demonstrates overloading the class gradedActivity

// Header guard
#ifndef CURVEDACTIVITY_H
#define CURVEDACTIVITY_H

#include "gradedActivityv3.h"

class curvedActivity : public gradedActivity
{
    protected:
        double rawS;    // Unadjusted score
        double percent; // Curve percentage
    public:
        // Default constructor
        curvedActivity() : gradedActivity()
        {
            rawS = 0.0;
            percent = 0.0;
        }

        // Mutator functions
        void setScore(double s)
        {
            rawS = s;
            gradedActivity::setScore(rawS * percent);
        }

        void setPerc(double c)
        {
            percent = c;
        }

        // Accessor functions
        double getPercentage() const
        {
            return percent;
        }

        double getRaw() const
        {
            return rawS;
        }
};
#endif

// Final exam header file
// found on page 873

// Header Guard
#ifndef FINALEXAM_H
#define FINALEXAM_H
#include "gradedActivityv1.h"

// Class declaration
// This denotes that finalExam is is derived from gradedActivity
// E.G. finalExam is a gradedActivity, much like a lion is a cat.
class finalExam : public gradedActivity
{
    private:
        int numQ;            // Number of questions
        double points;       // Point of each question
        int missed;          // Questions missed

    public: 
        // Default constructor
        finalExam()
        {
            numQ = 0;
            points =0;
            missed =0;
        }

        // Constructor
        finalExam( int questions, int missed)
        {
            set(questions, missed);
        }

        // Mutator function
        void set(int,int); // Defined in finalExam.cpp

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

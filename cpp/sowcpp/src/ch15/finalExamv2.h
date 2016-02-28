// Final exam version two header file
// found on page 879

#ifndef FINALEXAM_H
#define FINALEXAM_H
#include "gradedActivityv2.h"

// Final exam declaration
class finalExam : public gradedActivity
{
    private:
        int numQ;       // Holds the number of questions
        double points;  // Holds the number of points each question's worth
        int missed;     // Number of questions missed
    public:
        // Default constructor
        finalExam()
        {
            numQ = 0;
            points = 0.0;
            missed = 0;
        }

        // Constructor
        finalExam(int nquestions, int nmissed)
        {
            set(nquestions, nmissed);
        }

        // Mutator functions
        void set(int,int);  // Defined in finalExamv2.cpp
        void adjustScore();    // Defined in finalExamv2.cpp

        // Accessor functions
        double getQ() const
        {
            return numQ;
        }

        double getP() const
        {
            return points;
        }

        int getMissed() const
        {
            return missed;
        }
};

#endif

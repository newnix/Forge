// Graded Activity header file on page 871

// Header guard
#ifndef GRADEDACTIVITY_H
#define GRADEDACTIVITY_H

// Graded activity class declaration

class gradedActivity
{
    private:
        double score;   // Holds the numeric score
    public:
        // Default constructor
        gradedActivity()
            { score = 0.0; }

        // Constructor
        gradedActivity(double s)
            { score = s; }

        // Mutator function
        void setScore(double s)
            { score = s; }

        // Accessor functions
        double getScore() const
            { return score; }

        // Forward declaration
        char getLetter() const;
};

#endif

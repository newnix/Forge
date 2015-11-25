// Graded activity version two header file

// Header guard

#ifndef GRADEDACTIVITY_H
#define GRADEDACTIVITY_H

// gradedActivity class declaration

class gradedActivity
{
    protected:
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

        char getLetter() const;
};

#endif

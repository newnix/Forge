// Third version of the gradedActivity header file
// found on page 896
// Used to present the idea of overloading/redefining a base class function

// Header guard
#ifndef GRADEDACTIVITY_H
#define GRADEDACTIVITY_H

class gradedActivity
{
    protected:
        char letter;    // To hold the letter grade
        double score;   // To hold the numeric score
        void determineGrade()  // Determines the letter grade
        {
            if (score > 89)
            {
                letter = 'A';
            }
            else if (score > 79)
            {
                letter = 'B';
            }
            else if (score > 69)
            {
                letter = 'C';
            }
            else if (score > 59)
            {
                letter = 'D';
            }
            else
            {
                letter = 'F';
            }
        }
    public:
        // Default constructor
        gradedActivity()
        {
            letter = ' ';
            score = 0.0;
        }

        // Constructor with arguments
        gradedActivity(double s)
        {
            score = s;
            determineGrade();
        }

        // Mutator function
        void setScore(double s)
        {
            score = s;
            determineGrade();
        }

        // Accessor function
        double getScore() const
        {
            return score;
        }

        virtual char getLetter() const
        {
            return letter;
        }
};
#endif

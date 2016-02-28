// Practice program header file
// Student test scores.
// Is used to help demonstrate the concept of "Copy Constructors"
// found on page 14-4

#ifndef STUDENTTESTSCORES_H // Ensure only one copy of the header files exist
#define STUDENTTESTSCORES_H

#include <string>

const double DEFAULT_SCORE = 0.0;

class studentTestScores
{
    private:
        string stuName; // The student's name
        double *testScores; // Points to an array of test scores
        int numTestScores;  // Number of test scores

        // Private member function to create an array of test scores
        void createTestScoresArray( int size )
        {
            numTestScores = size;
            testScores = new double[size];
            for ( int i = 0; i < size; i++ )
            {
                testScores[i] = DEFAULT_SCORE;
            }
        }

        public:
            // Constructor
            studentTestScores( string name, int numScores )
            {
                stuName = name;
                createTestScoresArray( numScores );
            }

            // Destructor
            ~studentTestScores()
            {
                delete [] testScores;
            }

            // The setTestScore function sets a specific test scores value
            void setTestScore( double score, int index )
            {
                testScores[index] = score;
            }

            // Set the student's name
            void setStuName( string name )
            {
                stuName = name;
            }

            // Get the student name
            string getStuName() const
            {
                return stuName;
            }

            // Get the number of test scores
            int getNumTestScores() const
            {
                return numTestScores;
            }

            // Get a specific test score
            double getTestScore( int index ) const
            {
                return testScores[index];
            }
};
#endif

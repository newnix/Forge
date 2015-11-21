// Making changes to the other studentTestScores file
// This is adding the 'const' parameter in copy constructors.
// found on page 816.

#ifndef STUDENTTESTSCORES_H
#define STUDENTTESTSCORES_H

#include <string>

using namespace std;

const double DEFAULT_SCORE = 0.0;

class studentTestScores
{
    private:
        string stuName; // Student name
        double *testScores; // Points to an array of test scores
        int numTestScores;  // Number of test scores

        // Private mumber function to create an array of test scores
        void createTestScoresArray( int size )
        {
            numTestScores = size;
            testScores = new double[size];
            for (int i = 0; i < size; i++)
            {
                testScores[i] = DEFAULT_SCORE;
            }
        }

        public:
            // Constructor
            studentTestScores(string name, int numScores)
            {
                stuName = name;
                createTestScoresArray(numScores);
            }

            // Copy constructor
            studentTestScores(const studentTestSocers &obj)
            {
                stuName = obj.stuName;
                numTestScores = obj.numTestScores;
                testScores = new double[numTestScores];
                for (int i = 0; i < numTestScores; i++)
                {
                    testScores[i] = obj.testScores[i];
                }
            }

            // Destructor
            ~studentTestScores()
            { 
                delete [] testScores;
            }

            // The setTestScore function sets a specific test score's value
            void setTestScore(double score, int index)
            { testScores[index] = score; }

            // Set the student's name
            void setStudentName(string name)
            { stuName = name; }

            // Get the student's name
            string getStudentName() const
            { return stuName; }

            // Get the number of test scores
            int getNumTestScores() const
            { return numTestScores; }

            // Get a specific test score
            double getTestScore(int index) const
            { return testScores[index]; }
};
#endif

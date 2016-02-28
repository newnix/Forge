// Third version of studentTestScores.h
// Demonstrates overloading operators
// found on page 820.

#ifndef STUDENTTESTSCORES_H
#define STUDENTTESTSCORES_H

#include <string>

using namespace std;

const double DEFAULT_SCORE = 0.0;

class studentTestScores
{
    private:
        string stuName; // Student's name
        double *testScores; // Points to an array of test scores
        int numTestScores;  // Number of test scores

        // Private member function to create an array of test scores.
        void createTestScoresArray(int size)
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

            // Copy Constructor
            studentTestScores(const studentTestScores &obj)
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
            { delete [] testScores; }

            // The setTestScore function sets a specific test score's variable
            void setTestScore(double score, int index)
            {
                testScores[index] = score;
            }

            // Set the student's name
            void setStudentName(string name)
            {
                stuName = name;
            }

            // Get the student's name
            string getStudentName() const
            { return stuName; }

            // Get the number of test scores
            int getNumTestScores()
            { return numTestScores; }

            // Get a specific test score
            double getTestScore(int index) const
            { return testScores[index]; } 

            // Overloaded = operator
            void operator =(const studentTestScores &right)
            {
                delete [] testScores;
                stuName = right.stuName;
                numTestScores = right.numTestScores;
                testScores = new double[numTestScores];
                for (int i = 0; i < numTestScores; i++)
                {
                    testScores[i] = right.testScores[i];
                }
            }
};
#endif

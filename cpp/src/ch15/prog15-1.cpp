// Practice program 15-1
// found on page 872
// This demonstrates the gradedActivity class

#include <iostream>
#include "gradedActivityv1.h"

using namespace std;

int main()
{
    double testScore;   // To hold the test score

    // Create a gradedActivity object for the test
    gradedActivity test;

    // Get a numeric test score from the user
    cout << "Enter your numeric test score: ";
    cin >> testScore;

    // Store the numeric score in the test object
    test.setScore(testScore);

    // Display the letter grade for the test
    cout << "The grade for the test is " << test.getLetter() << endl;

    return 0;
}

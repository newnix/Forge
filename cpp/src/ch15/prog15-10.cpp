// Practice program 15-10
// found on page 908
// Expand upon prog15-9

#include <iostream>
#include <iomanip>
#include "passFail.h"

using namespace std;

// Function prototype
void displayGrade(const gradedActivity &);

int main()
{
    // Create a passFail activity object. Minimum passing score is 70.
    passFail test(70);

    // Set the score to 72
    test.setScore(72);

    // Display the object's grade data. The letter grade should be 'P'
    displayGrade(test);

    return 0;
}

/*
 * The displayGrade function displays a gradedActivity object's 
 * numerical score and letter grade
 */

void displayGrade(const gradedActivity &activity)
{
    cout << setprecision(2) << fixed;
    cout << "The activity's numeric score is " << activity.getScore() << endl;
    cout << "The student's letter grade is " << activity.getLetter() << endl;
}

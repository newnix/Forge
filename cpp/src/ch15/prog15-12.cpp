// Practice program 15-12
// found on page 912
// This program demonstrates polymorphism with the virtual function type

#include <iostream>
#include <iomanip>
#include "passFailExam.h"

using namespace std;

// Function prototype
void displayGrade(const gradedActivity &);

int main()
{
    // Create a gradedActivity object
    gradedActivity test1(88.0);

    // Create a passFailExam object.
    // There are 100 questions, the student missed 25 of them, and the minimum passing score is 70.
    passFailExam test2(100, 25, 70.0);

    // Display the grade data for both objects
    cout << "Test 1: "; displayGrade(test1); cout << endl;  // Graded activity object
    cout << "Test 2: "; displayGrade(test2); cout << endl;  // PassFailExam object

    return 0;
}

/*
 * The displayGrade function definition.
 * This function display's a gradedActivity's numeric score and letter grade.
 */

void displayGrade(const gradedActivity &activity)
{
    cout << setprecision(2) << fixed;
    cout << "The activity's numeric score is " << activity.getScore() << endl;
    cout << "The activity's letter grade is " <<activity.getLetter() << endl;
}

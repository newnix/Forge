// Practice program 15-13
// found on page 914
// This program is functionally the same as prog15-12, but instead of a reference variable, we use a pointer.

#include <iostream>
#include <iomanip>
#include "passFailExam.h"

using namespace std;

// Function prototype with a pointer
void displayGrade(const gradedActivity *);

int main()
{
    // Create a gradedActivity object
    gradedActivity test1(88.0);

    // Create a passFailExam object. 
    // There are 100 questions, missed 25, min passing grade is 70
    passFailExam test2(100, 25, 70);

    // Display the grade data for both objects
    cout << "Test 1: "; displayGrade(&test1); cout << endl; // Use the address of test1
    cout << "Test 2: "; displayGrade(&test2); cout << endl; // Use the address of test2

    return 0;
}

/*
 * The displayGrade function displays a gradedActivity object's
 * numeric score and letter grade. This version of the function uses a pointer
 * to gradedActivity objects as its parameter.
 */

void displayGrade(const gradedActivity *activity)
{
    cout << setprecision(2) << fixed;
    cout << "The activity's numeric score is " << activity -> getScore() << endl;
    cout << "The activity's letter grade is " << activity -> getLetter() << endl;
}

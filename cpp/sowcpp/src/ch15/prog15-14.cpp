// Practice program 15-14, found on page 915
// This program is functionally the same as 15-12 and 15-13
// This program uses a pointer for class creation instead of pointers for value assignment

#include <iostream>
#include <iomanip>
#include "passFailExam.h"

using namespace std;

// Function prototype declaration
void displayGrade(const gradedActivity *);

int main()
{
    // constant for the size of an array
    const int NUM_TESTS = 4;

    // Tests is an array of gradedActivity pointers.
    // Each element of tests is initialized 
    // with the address of a dynamically allocated object.

    gradedActivity *tests[NUM_TESTS] = 
    {
        new gradedActivity(88.0),
        new passFailExam(100, 25, 70.0),
        new gradedActivity(67.0),
        new passFailExam(50, 12, 60.0)
    };

    // Display the grade data for each element in the array
    for (int count = 0; count < NUM_TESTS; count++)
    {
        cout << "Test #" << (count + 1) << ":\n";
        displayGrade(tests[count]);
        cout << endl;
    }

    return 0;
}

/*
 * Definition of the function displayGrade(const gradedActivity *)
 * This function converts the numeric score of an exam into a letter grade.
 * This version of the function uses a gradedActivity pointer as its parameter.
 */

void displayGrade(const gradedActivity *activity)
{
    cout << setprecision(2) << fixed;
    cout << "The activity's numeric score is " << activity -> getScore() << endl;
    cout << "The actvitiy's letter grade is " << activity -> getLetter() << endl;
}


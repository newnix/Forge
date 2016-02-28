// Practice program 15-7
// found on page 899
// This program demonstrates
// a class that redefines a base class function

#include <iostream>
#include <iomanip>
#include "curvedActivity.h"

using namespace std;

int main()
{
    double numScore;    // Holds the numeric score
    double percentage;  // Holds the curve percentage

    // Define a curvedActivity object
    curvedActivity exam;

    // Get the unadjusted score
    cout << "Enter the student's raw numerical score: ";
    cin >> numScore;

    // Get the percentage on the curve
    cout << "Enter the curve percentage for this student: ";
    cin >> percentage;

    // Send the values to the exam object
    exam.setPerc(percentage);
    exam.setScore(numScore);

    // Display the grade data
    cout << fixed << setprecision(2);
    cout << "The raw score is " << exam.getRaw() << endl;
    cout << "The curved score is " << exam.getScore() << endl;
    cout << "The curved grade is: " << exam.getLetter() << endl;

    return 0;
};

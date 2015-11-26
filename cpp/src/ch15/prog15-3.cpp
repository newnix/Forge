// This is practice program 15-3 found on page 881
// This program demonstrates a base class with a protected member

#include <iostream>
#include <iomanip>
#include "finalExamv2.h"

using namespace std;

int main()
{
    int questions;  // Holds the number of questions on the exam
    int missed;     // Number of questions missed by the student

    // Get the number of questions on the final exam
    cout << "How many questions were on the final exam? ";
    cin >> questions;

    // Get the number of questions
    cout << "How many questions were missed? ";
    cin >> missed;

    // define a finalExam object and initialize it with the values entered
    finalExam test(questions, missed);

    // Display the test results
    cout << setprecision(2) << fixed;
    cout << "\nEach question counts " << test.getP() << " points each.\n";
    cout << "The adjusted exam score is " << test.getScore() << endl;
    cout << "The exam grade is " << test.getLetter() << endl;

    return 0;
}

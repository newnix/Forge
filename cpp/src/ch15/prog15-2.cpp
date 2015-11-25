// Practice program 15-2
// found on page 876
// demonstrates a base class and a derived class

#include <iostream>
#include <iomanip>
#include "finalExam.h"

using namespace std;

int main()
{
    int questions;  // Questions on the exam
    int missed;     // Questions missed

    // Get the number of questions on the exam
    cout << "How many questions are on the final exam? ";
    cin >> questions;

    // Get the number of questions the student missed
    cout << "How many questions were missed? ";
    cin >> missed;

    // Define a finalExam object and initialize it with the values entered
    finalExam test(questions, missed);

    // Display the test results
    cout << setprecision(2);
    cout << "\nEach question counts " << test.getPoints() << " points each.\n";
    cout << "The exam score is " << test.getScore() << endl;
    cout << "The exam grade is " << test.getLetter() << endl;

    return 0;
}


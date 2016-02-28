// Practice program 15-9
// found on page 904
// Demonstrates nested classes

#include <iostream>
#include <iomanip>
#include "passFailExam.h"

using namespace std;

int main()
{
    int questions;  // Holds the number of questions
    int missed;     // Holds the number of questions missed
    double minPassing;  // Minimum passing score

    // Get the number of questions on the exam
    cout << "How many questions are on the exam? ";
    cin >> questions;

    // Get the number of questions the student missed
    cout << "How many questions did the student miss? ";
    cin >> missed;

    // Get the minimum passing score
    cout << "Enter the minimum passing score for this test: ";
    cin >> minPassing;

    // Define a passFail object
    passFailExam exam(questions, missed, minPassing);

    // Display the test results
    cout << fixed << setprecision(2);
    cout << "\nEach question counts " << exam.getPoints() << " points each.\n";
    cout << "The minimum passing score is " << exam.getMinPassingScore() << endl;
    cout << "The student's exam score is " << exam.getScore() << endl;
    cout << "The student's grade is " << exam.getLetter() << endl;

    return 0;
}

// Practice program 14-6 on page 822
// This uses the most recent version of the studentTestScores.h  file
// Demonstrates the overloaded '=' operator
#include <iostream>
#include "studentTestScoresv3.h"
using namespace std;

// Function prototype
void displayStudent(studentTestScores);

int main()
{
    // Create a studentTestScores object and assign scores.
    studentTestScores student1("Kelly Thorton", 3);
    student1.setTestScore(100.0, 0);
    student1.setTestScore(95.0, 1);
    student1.setTestScore(80, 2);

    // Create another studentTestScore object with default scores.
    studentTestScores student2("Jimmy Griffin", 5);

    // Assign the student1 object to student2
    student2 = student1;

    // Display both objects. They should be identical.
    displayStudent(student1);
    displayStudent(student2);
    return 0;
}

/*
 * displayStudent definition.
 * This function accepts a studentTestScores object data
 */

void displayStudent(studentTestScores s)
{
    cout << "Name: " << s.getStudentName() << endl;
    cout << "Test Scores: ";
    for (int i = 0; i < s.getNumTestScores(); i++)
    {
        cout << s.getTestScore(i) << " ";
    }
    cout << endl;
}

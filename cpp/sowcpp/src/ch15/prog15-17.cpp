// Practice program 15-17
// found on page 924
// This program demonstrates the csStudent class
// which is derived from the abstract base class, student.

#include <iostream>
#include "csStudent.h"

using namespace std;

int main()
{
    // Create a CS student object for a student
    csStudent student("Jennifer Haynes", "167W98337", 2006);

    // Store values for math, cs, and general education hours
    student.setMathHours(12);   // Student has taken 12 math hours
    student.setCsHours(20);     // Student has taken 20 cs hours
    student.setGenEdHours(40);  // Student has taken 40 gen ed hours

    // Display the number of remaining hours
    cout << "The student " << student.getName() << " needs to take " << student.getRemainingHours()
    << " more hours to graduate." << endl;

    return 0;
}

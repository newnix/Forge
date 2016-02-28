// Practice program 11-8 found on page 619
// Demonstrates using pointers to a structure variable as a parameter

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct student
{
    string name;        // Student name
    int idnum;          // Student ID
    int credithours;    // Credit hours enrolled
    double gpa;         // Current gpa
};

void getData(student *);    // Function prototype

int main()
{
    student freshman;

    // Get the student data
    cout << "Enter the following student data:\n";
    getData(&freshman); // Pass the address of freshman
    cout << "\nHere is the student data you entered: \n";

    // Now display the data stored in freshman
    cout << setprecision(3);
    cout << "Name: " << freshman.name << endl;
    cout << "ID Number: " << freshman.idnum << endl;
    cout << "Credit Hours: " << freshman.credithours << endl;
    cout << "GPA: " << freshman.gpa << endl;

    return 0;
}

/*
 * Definition of getData
 * Uses a pointer to a student structure variable
 * The user enters student info which is then stored in the variable
 * The operator "->" allows us to address structure variables that are being pointed to
 */

void getData(student *s)
{
    // Get the student name
    cout << "Student Name: ";
    getline(cin, s->name);

    // Get the student ID number
    cout << "Student ID: ";
    cin >>  s->idnum;

    // Get the enrolled credit hours
    cout << "Enrolled credit hours: ";
    cin >> s->credithours;

    // Get the GPA
    cout << "Current GPA: ";
    cin >> s->gpa;
}

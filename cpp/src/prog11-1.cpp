// Practice Program 11-1 on page 599
// Demonstrates the use of data structures

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct PayRoll
{
    int empNumber;  // Employee Number
    string name;    // Employee's Name
    double hours;   // Hours Worked
    double PayRate; // Hourly Wage
    double GrossPay;    // Pay pre-taxes
};

int main()
{
    PayRoll employee; //employee is a PayRoll structure

    // Get the Employee's number
    cout << "Enter the Employee's number: ";
    cin >> employee.empNumber;

    // Get the Employee's name
    cout << "Get the Employee's name: ";
    cin.ignore();   // To skip the remaining '\n' character
    getline(cin, employee.name);

    // Get the hours worked by the Employee
    cout << "How many hourse did the Employee work? ";
    cin >> employee.hours;

    // Get the Employee's hourly pay rate
    cout << "What is the Employee's hourly wage? ";
    cin >> employee.PayRate;

    // Calculate the Employee's gross pay
    employee.GrossPay = employee.hours * employee.PayRate;

    // Display the Employee's data
    cout << endl;
    cout << endl;
    cout << "Here's the employee's payroll data:\n";
    cout << "Name: " << employee.name << endl;
    cout << "Number: " << employee.empNumber << endl;
    cout << "Hours worked: " << employee.hours << endl;
    cout << "Pay rate: " << employee.PayRate << endl;
    cout << fixed << showpoint << setprecision(2);
    cout << "Gross pay: $" << employee.GrossPay << endl;
    
    return 0;
}

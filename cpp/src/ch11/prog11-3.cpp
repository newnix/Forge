// Practice program 11-3 found on page 603
// This demonstrates partially initialized structure variables

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct employeePay
{
    string name;        // Employee name
    int empNum;         // Employee id
    double payRate;     // Hourly pay
    double hours;       // Hours worked
    double grossPay;    // Gross pay
};

int main()
{
    employeePay employee1 = {"Betty Ross", 141, 18.75};
    employeePay employee2 = {"Jill Sandburg", 142, 17.50};

    cout << fixed << showpoint << setprecision(2);

    // Calculate pay for employee1
    cout << "Name: " << employee1.name << endl;
    cout << "Employee Number: " << employee1.empNum << endl;
    cout << "Enter the hours worked by this employee: ";
    cin >> employee1.hours;
    employee1.grossPay = employee1.hours * employee1.payRate;
    cout << "Gross pay: $" << employee1.grossPay << endl << endl;

    // Calculate pay for employee 2
    cout << "Name: " << employee2.name << endl;
    cout << "Employee Number: " << employee2.empNum << endl;
    cout << "Enter the hours worked by this employee: ";
    cin >> employee2.hours;
    employee2.grossPay = employee2.hours * employee2.payRate;
    cout << "Gross pay: $" << employee2.grossPay << endl;

    return 0;
}

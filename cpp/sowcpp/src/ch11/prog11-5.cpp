// Practice program 11-5 found on page 609
// This program demonstrates the use of nested structures
#include <iostream>
#include <string>
using namespace std;

// This data structure holds data about a date
struct date
{
    int month;
    int day;
    int year;
};

// The Place structure holds a physical address
struct place
{
    string address;
    string city;
    string state;
    string zip;
};

// The EmployeeInfo structure holds an employee's data
struct employeeInfo
{
    string name;
    int employeeNum;
    date birthdate;     // Nested structure
    place residence;    // Nested structure
};

int main()
{
    // Define a structure variable to hold info about the manager.
    employeeInfo manager;

    // Get the manager's name and employee number
    cout << "Enter the manager's name: ";
    getline(cin, manager.name);
    cout << "Enter the manager's employee number: ";
    cin >>  manager.employeeNum;

    // Get the manager's birth date
    cout << "Now enter the manager's date of birth.\n";
    cout << "Month (up to 2 digits): ";
    cin >> manager.birthdate.month;
    cout << "Day (up to 2 digits): ";
    cin >>  manager.birthdate.day;
    cout << "Year: ";
    cin >> manager.birthdate.year;
    cin.ignore();   // Skips the remaining newline character

    // Get the manager's residence information
    cout << "Enter the manager's street address: ";
    getline(cin, manager.residence.address);
    cout << "City: ";
    getline(cin, manager.residence.city);
    cout << "State: ";
    getline(cin, manager.residence.state);
    cout << "And the zip code: ";
    getline(cin, manager.residence.zip);

    // Now display the information entered
    cout << "\nHere's  the manager's information:\n";
    cout << manager.name << endl;
    cout << "Employee number: " << manager.employeeNum << endl;
    cout << "Date of birth: ";
    cout << manager.birthdate.year << "-";
    cout << manager.birthdate.month << "-";
    cout << manager.birthdate.day << endl;
    cout << "Place of residence:\n";
    cout << manager.residence.address << endl;
    cout << manager.residence.city << ", ";
    cout << manager.residence.state << ", " << endl;
    cout << manager.residence.zip << endl;

    return 0;
}

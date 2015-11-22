// Practice program 12-15, on page 680
// This program uses a structure variable to store a record to a file.

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

// Array sizes
const int NAME_SIZE = 51, ADDR_SIZE = 51, PHONE_SIZE = 14;

// Declare a structure for the record
struct info
{
    char name[NAME_SIZE];
    int age;
    char address1[ADDR_SIZE];
    char address2[ADDR_SIZE];
    char phone[PHONE_SIZE];
};

int main()
{
    info person;    // To hold info about a person
    char again;     // To hold y/n

    // Open a file for binary output
    fstream people("people.dat", ios::out | ios::binary);

    do
    {
        // Get data about a person.
        cout << "Enter the following data about a person: " << endl;
        cout << "Name: ";
        cin.getline(person.name, NAME_SIZE);
        cout << "Age: ";
        cin >> person.age;
        cin.ignore();   // Skip over the remaining newline char
        cout << "Address line 1: " ;
        cin.getline(person.address1, ADDR_SIZE);
        cout << "Address line 2: ";
        cin.getline(person.address2, ADDR_SIZE);
        cout << "Phone: ";
        cin.getline(person.phone, PHONE_SIZE);

        // Write the contents of the person structure to the file
        people.write(reinterpret_cast<char *>(&person), sizeof(person));

        // Deermine whether or not the user wants to enter another record
        cout << "Do you want to enter another record? [Y/N]" << endl;
        cin >> again;
        cin.ignore();   // Skip that pesky newline char
    } while (toupper(again) == 'Y');

    // Close the file
    people.close();

    return 0;
}

// Practice program 12-16, on page 681
// This program uses a structure variable to read information from a file
// Adds readback functionality to prog12-15

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

const int NAME_SIZE = 51, ADDR_SIZE = 51, PHONE_SIZE = 14;

// Declare a structure to hold the record info
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
    info person;    // Holds info about a person
    char again;     // To hold a yes/no response
    fstream people; // File stream object

    // Open the file for input in binary mode
    people.open("people.dat", ios::in | ios::binary);

    // Test for errors
    if (!people)
    {
        cout << "ERROR: Cannot open file. Aborting..." << endl;
        return 0;
    }

    cout << "Here are the people in the file: \n\n";

    // Read the first record from the file
    people.read(reinterpret_cast<char *>(&person), sizeof(person));

    // While not at the end of the file, display the records.
    while(!people.eof())
    {
        // Display the record
        cout << "Name: ";
        cout << person.name << endl;
        cout << "Age: ";
        cout << person.age << endl;
        cout << "Address, line 1: ";
        cout << person.address1 << endl;
        cout << "Address, line 2: ";
        cout << person.address2 << endl;
        cout << "Phone number: ";
        cout << person.phone << endl;

        // Wait for the user to hit the enter key
        cout << "\nPress the Enter key to see the next record.\n";
        cin.get(again);

        // Read the next record from the file.
        people.read(reinterpret_cast<char *>(&person), sizeof(person));

    }

    cout << "That's all the data in the file!" << endl;
    people.close(); // Close the file

    return 0;
}

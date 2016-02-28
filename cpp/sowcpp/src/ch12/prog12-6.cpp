// Practice program 12-6, found on page 663
// This program demonstrates the return value of the stream
// object error testing number functions.

#include <iostream>
#include <fstream>

using namespace std;

// Prototype function
void show(fstream &);

int main()
{
    int num = 10;

    // Open the file for output
    fstream file("stuff.dat", ios::out);
    if (file.fail())
    {
        cout << "ERROR: Cannot open the file." << endl;
        return 0;
    }

    // Write a value to the file
    cout << "Writing the value " << num << " to the file." << endl;
    file << num;

    // Show the bit states
    show(file);

    // Close the file
    file.close();

    // Reopen the file for input
    file.open("stuff.dat", ios::in);
    if (file.fail())
    {
        cout << "ERROR: Cannot open the file." << endl;
        return 0;
    }

    // Read the only value from the file
    cout << "Reading from the file." << endl;
    file >> num;
    cout << "The value " << num << " was read." << endl;

    // Show the bit states
    show(file);

    // No more data is in the file, but force a bad read operation
    cout << "Forcing an invalid read operation..." << endl;
    file >> num;

    // Show the bit state
    show(file);

    // Close the file, for good
    cout << "Closing file and terminating program..." << endl;
    file.close();
    return 0;
}

/*
 * Definition of the funtction show.
 * This function uses an fstream reference object as its sole parameter.
 * The return values are eof(), fail(), bad(), and good()
 * member functions are displayed.
 * The clear() function is called before the function returns
 */

void show(fstream &file)
{
    cout << "File status: " << endl;
    cout << " eof bit: " << file.eof() << endl;
    cout << " fail bit: " << file.fail() << endl;
    cout << " bad bit: " << file.bad() << endl;
    cout << " good bit: " << file.good() << endl;
    file.clear();   // Clear any bad bits before proceeding
}

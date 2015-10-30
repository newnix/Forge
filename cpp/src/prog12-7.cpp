// Practice program 12-7, on page 665
// This program demonstrates how the >> operator
// should not be used to read data that contains whitespace characters from a file.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input;   // To hold file input
    fstream file;   // File stream object

    // Open the file in unput mode
    file.open("murphy.txt", ios::in);

    // If the file was successfully opened, continue.
    if (file)
    {
        // Read the file contents
        while (file >> input)
        {
            cout << input;
        }

        // Close the file
        file.close();
    }

    else
    {
        cout << "ERROR: Cannot open file." << endl;
    }

    return 0;
}

/*
 * The problem in this program can be solved with a different function call
 * getline(file, str, '\n');
 */


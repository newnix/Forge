// Practice program 12-9, on page 668
// This file demonstrates the getline function witha specified delimiter

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string input;   // To hold the file input

    // Open the file for input
    fstream file("murphy.txt", ios::in);

    // If the file was successfully opened
    if (file)
    {
        // Read an item using $ as a delimiter
        getline(file, input, '$');
        
        // While the last read operation was successful
        // continue
        while(file)
        {
            // Display the last item read
            cout << input << endl;

            // Read an item using '$' as a delimiter
            getline(file, input, '$');
        }

        // Close the file
        file.close();

    }
    else
    {
        cout << "ERROR: could not open the file." << endl;
    }

    return 0;
}

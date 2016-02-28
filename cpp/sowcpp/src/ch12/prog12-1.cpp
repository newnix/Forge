// Practice program 12-1
// This program uses an fstream object to write data to a file

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream dataFile;   // Creates a fstream object called "dataFile"

    cout << "Opening file...\n";    // Open the file for output
    dataFile.open("demofile.txt", ios::out);
    cout << "Now writing info to the data file.\n";
    dataFile << "Jones\n";
    dataFile << "Smith\n";
    dataFile << "C++\n";
    dataFile.close();           // Close the file
    cout << "Done.\n";

    return 0;
}

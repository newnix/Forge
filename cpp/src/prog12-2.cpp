// Practice program 12-2, page 655
// This opens a file, writes data to it, closes the file
// Then reopens and writes more info to it

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream file;

    cout << "Opening file...\n";

    // Open the file in output mode.
    file.open("demofile.txt", ios::out);
    cout << "Now writing data to the file.\n";
    file << "something else\n";
    file << "yet another thing\n";
    cout << "Now closing the file.\n";
    file.close();   // Close the file

    cout << "Opening the file again...\n";
    file.open("demofile.txt", ios::out | ios::app);
    cout << "Writing more info to the file.\n";
    file << "Hey! I'm back!\n";
    file << "Closing it again now.\n";
    cout << "Closing the file for real now.\n";
    file.close();

    cout << "Done." << endl;
    return 0;
}

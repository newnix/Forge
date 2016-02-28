// Practice program 12-5 found on page 660
// This program demonstrates how file stream
// objects can be passed to functions

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Prototype function
void show(fstream &);
bool openfile(fstream &, string);

int main()
{
    fstream file;

    if (openfile(file, "demofile.txt"))
    {
        cout << "File opened successfully!" << endl;
        cout << "Now sending data from the file..." << endl;
        show(file);
        file.close();
        cout << "Done." << endl;
    }

    else
        cout << "Error opening the file!" << endl;

    return 0;
}

/*
 * Definition of the function openfile. 
 * Accepts a reference to an fstream object as an argument.
 * The file is opened for input
 * If this is successful, the function returns true
 */

bool openfile(fstream &file, string name)
{
    file.open(name.c_str(), ios::in);
    if (file.fail())
        return false;
    else
        return true;
}

/*
 * Definition of the funcition show.
 * Accepts an fstream reference as its sole argument.
 * uses a loop to read from the file and print to stdout.
 */

void show(fstream &file)
{
    string line;

    while (file >> line)
    {
        cout << line << endl;
    }
}

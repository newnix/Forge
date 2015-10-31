// Practice program 12-12 on page 673
// This demonstrates reading from one file and writing to another

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>   // Needed for the toupper function call

using namespace std;

int main()
{
    string filename;    // Hold a filename
    char ch;            // Hold a char
    ifstream infile;    // Input file

    // Open a file for output
    ofstream outfile("out.txt");

    // Get the input file name
    cout << "Enter a file name: " << endl;
    cin >> filename;

    // Open the file for input
    infile.open(filename.c_str());

    // If the file opened successfully, continue
    if(infile)
    {
        // Read a char from file 1.
        infile.get(ch);

        // While the last read operation was successful, continue
        while(infile)
        {
            // Write uppercase char to file 2.
            outfile.put(toupper(ch));

            // Read another char from file 1.
            infile.get(ch);
        }

        // Close the two files
        infile.close();
        outfile.close();
        cout << "File conversion complete!" << endl;
    }

    else
    {
        cout << "ERROR: Cannot open "<< filename << endl;
    }

    return 0;
}

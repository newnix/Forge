// Practice program 12-8, on page 667
// This program uses the getline function
// to fix the problem posed in 12-8

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string input;   // Holds the file input
    fstream file;   // Filestream object

    // Open the file in input mode
    file.open("murphy.txt", ios::in);

    // If the file was successfully opened, continue
    if (file)
    {
        // Read an item from the file
        getline(file, input);

        // While the last read op was successful, continue
        while (file)
        {
            // Display the last item read
            cout << input << endl;

            // Read the next item
            getline(file, input);

        }

        // Close the file
        file.close();
    }
    else
    {
       cout << "ERROR: Cannot open the file." << endl;
    }
    
    return 0;
}

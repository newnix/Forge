// Practice Program 12-3 on page 658
// Uses setprecision and fixed to format output to a file

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    fstream file;
    double num = 17.816932;

    file.open("numfile.txt", ios::out);    // Open the file in output mode

    file << fixed;  // Use fixed-point notation
    file << num << endl;

    // Format the output for varying decimal points
    
    file << setprecision(4);
    file << num << endl;

    file << setprecision(3);
    file << num << endl;

    file << setprecision(2);
    file << num << endl;

    file << setprecision(1);
    file << num << endl;
    
    cout << "done" << endl;
    file.close();
    return 0;
}

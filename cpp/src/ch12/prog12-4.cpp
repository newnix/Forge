// Practice program 12-4, found on page 659
// This program writes three lines of numbers to the file

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    const int ROWS = 3;     // Rows to write
    const int COLS = 3;     // Columns to write
    int nums[ROWS][COLS] = { 2897, 5, 837,
                              34, 7, 1263,
                              390, 3456, 12};
    fstream ofile("table.txt", ios::out);

    // Write the three rows of numbers with each
    // number in a field of 8 character spaces.

    for (int row=0; row < ROWS; row++)
    {
        for (int col=0; col < COLS; col++)
        {
            ofile << setw(8) << nums[row][col];
        }
        ofile << endl;
    }

    ofile.close();
    cout << "Done." << endl;
    
    return 0;
}

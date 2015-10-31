// Practice program 12-14, on page 678
// This program also uses the read and write functions

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    const int SIZE = 10;
    fstream file;
    int num[SIZE] = {1,2,3,4,5,6,7,8,9,10};

    // Open the file for output in binary mode
    file.open("numbers.dat", ios::out | ios::binary);

    // Write the contents of the array to the file
    cout << "Writing the data to the file." << endl;
    file.write(reinterpret_cast<char *>(num), sizeof(num));

    // Close the file.
    file.close();

    // Open the file for input in binary mode
    file.open("numbers.dat", ios::in | ios::binary);

    // Read the contents of the file back into the array
    cout << "Now reading the data back into memory." << endl;
    file.read(reinterpret_cast<char *>(num), sizeof(num));

    // Display the contents of the array.
    for (int count = 0; count < SIZE; count++)
    {
        cout << num[count] << " ";
    }
    cout << endl;

    // Close the file again
    file.close();

    return 0;
}

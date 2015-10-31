// Practice program 12-11, found on page 670
// This program demonstrates the put member function

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char ch;    // To hold a character

    // Open the file for output
    fstream file("sentence.txt", ios::out);

    cout << "Type a sentence and be sure to end it with a ";
    cout << "period.\n (One of these: '.')\n";

    // Get a sentence from the user one character at a time
    // Then write each char to the file.
    cin.get(ch);
    while (ch != '.')
    {
        file.put(ch);
        cin.get(ch);
    }

    file.put(ch);   // Write the period
    
    // Close the file.
    file.close();
    return 0;
}

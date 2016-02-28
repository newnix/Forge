// Converting a string to Morse Code
// Problem 17 on page 591

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

string toMorseCode(string);

int main()
{
    string plainText;
    char ans;
    cout << "This program will convert a given string to Morse code." << endl;
        
    do
    {   // Get the plainText string
        cout << "Enter a string to have converted to Morse code: ";
        cin >> plainText;

        cout << "The string is : " << toMorseCode(plainText) << endl;
        cout << "Would you like to translate another string? (Y/N)" << endl;
        cin >> ans;

        while (toupper(ans) != 'Y' && toupper(ans) != 'N')
        {
            cout << "Please enter either 'Y' or 'N' : " << endl;
            cin >> ans;
        }

    } while(toupper(ans) == 'Y');
    return 0;
}

string toMorseCode(string english)
{
    string morselib[40] = {" ","--..--",".-.-","..--..","-----",".----","..---","...--","....-",".....","-....","--...","---..","----."
                    ,".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-"
                    ,".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
    string translib[40] = {" ",",",".","?","0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L",
                    "M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
    string morseString;
    return morseString;
}

// Programming assignment #5
// manipulating information kept in a file

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Declare function prototypes
void addRecord(fstream &);
void viewRecord(fstream &);
void changeRecord(fstream &);

int main()
{
    int opt;
    do
    {
        // Prompt the user for function selection
        cout << "Select a function [1-3]:\n\n";
        cout << "[1] Add a record to the inventory file" << endl;
        cout << "[2] View the records in the inventory file" << endl;
        cout << "[3] Change the records in the inventory file" << endl;
        cout << "[0] Exit"<< endl;

        cin >> opt;
        
        // Use the user input to call the desired function
        switch (opt)
        {
            case 1 : cout << "This would run the addRecord function" << endl;
                break;
            case 2 : cout << "This would have displayed the file" << endl;
                break;
            case 3 : cout << "This would have allowed you to modify an entry" << endl;
                break;
            default:
                break;
        }

    // So long as the user doesn't enter '0' keep the program running   
    }while(opt != 0);
    return 0;
}

/*
// Define addRecord(fstream &);
void addRecord(string &)
{
    cout << "New inventory entry: ";
}
*/

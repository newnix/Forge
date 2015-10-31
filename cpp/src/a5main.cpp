// Programming assignment #5
// manipulating information kept in a file

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

// Declare function prototypes
void addRecord(fstream &);
void viewRecord(fstream &);
void changeRecord(fstream &);

const short DESC_NUM = 51, DATE = 12;

struct inventory
{
    char item[DESC_NUM];
    int stock;
    float wsale;
    float rsale;
    char date[DATE];
};

// declared here to be usable in the function definitions
inventory inv;  // Holds the inventory entries

int main()
{
    fstream record; // Writes to an inventory file
    int opt;        // Selects the function to be used

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
            case 1 : addRecord(record);
                break;
            case 2 : viewRecord(record);
                break;
            case 3 : changeRecord(record);
                break;
            default:
                break;
        }

    // So long as the user doesn't enter '0' keep the program running   
    }while(opt != 0);
    
    record.close(); // Close the file before exiting the program

    return 0;
}


// Define addRecord
void addRecord(fstream &file)
{
    char again; // Determine if the user wants to add another item to inventory.
    cout << "New inventory entry selected. " << endl;
    
    // Open the file for writing
    file.open("inv.dat", ios::out | ios::app);
    

    cout << "\nEnter the attributes for this entry below.\n\n";
    cout << "Enter the item description: ";
    cin.ignore();
    cin.getline(inv.item, DESC_NUM);
    cout << "Number of units in stock: ";
    cin >> inv.stock;
    cin.ignore();   // Make sure to ignore that newline character
    cout << "Price wholesale: ";
    cin >> inv.wsale;
    cin.ignore();
    cout << "Price retail: ";
    cin >> inv.rsale;
    cout << "Date recieved: ";
    cin.ignore();
    cin.getline(inv.date, DATE);

    file.write(reinterpret_cast<char *>(&file), sizeof(file));
    file.close();

}

// Define viewRecord
void viewRecord(fstream &file)
{
    char i;
    cout << "\nDisplaying the current inventory list..." << endl;
    
    // Open the file as being readable
    file.open("inv.dat", ios::in);

    // Read the first record from the file
    file.read(reinterpret_cast<char *>(&file), sizeof(file));

    // Keep displaying the inventory as long as the end of file hasn't been reached
    while(!file.eof())
    {
        cout << "Item: " << inv.item << endl;
        cout << "Number in stock: " << inv.stock << endl;
        cout << "Price wholesale: "<< fixed << setprecision(2) << inv.wsale << endl;
        cout << "Price resale: " << fixed << setprecision(2) << inv.rsale << endl;
        cout << "Date recieved: " << inv.date << endl;

        // Wait for the user to hit enter
        cout << "\nPress the enter key to see the next entry.\n";
        cin.get(i);

        // Read the next record in the file
        file.read(reinterpret_cast<char *>(&file), sizeof(file));
    }
    
    cout << "\nThat's all the entries currently in the file.\n";
    file.close();
}

// Define changeRecord
void changeRecord(fstream &file)
{
    // Placeholder statement, needs to be replaced.
    cout << "Allowing you to change an entry: " << endl;
}


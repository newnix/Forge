// Practice Program 11-6 found on page 613
// Demonstrates the use of structure variables as arguments

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct inventoryItem
{
    int partNum;        // Part number
    string description; // Part description
    int onHand;         // Number of items on hand
    double price;       // Price of the item
};

// Function Prototypes
void getItem(inventoryItem&);    // Argument passed by reference
void showItem(inventoryItem);    // Argument passed by value

int main()
{
    inventoryItem part;

    getItem(part);
    showItem(part);
    
    return 0;
}

/*
 * Definition of getItem
 * This uses a structure reference variable as its parameter
 * It asks the user for information to store in the structure
 */

void getItem(inventoryItem &p)  // Uses a reference parameter
{
    // Get the part number.
    cout << "Enter the part number: ";
    cin >> p.partNum;

    // Get the part description
    cout << "Enter the part description: ";
    cin.ignore(); // Ignore the newline character
    getline(cin, p.description);

    // Get the quantity on hand
    cout << "Enter the current inventory: ";
    cin >> p.onHand;

    // Get the unit price
    cout << "Enter the price of the item: ";
    cin >> p.price;
}

/*
 * Definition of showItem
 * This uses the previously built structure and displays its contents
 */

void showItem(inventoryItem p)
{
    cout << fixed << showpoint << setprecision(2) << endl;
    cout << "Part Number: " << p.partNum << endl;
    cout << "Description: " << p.description << endl;
    cout << "Units in Stock: " << p.onHand << endl;
    cout << "Price: $" << p.price << endl;
}

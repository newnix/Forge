// The pseudocode plan for assignment 4
// This needs to simulate a vending machine
#include <iostream>
#include <string>
using namespace std;

struct drink
{
    string flavor;      // Holds the flavor of the drink
    double cost;        // Holds the cost of each drink
    int inv;            // Number of drinks in the machine
};

// Function prototypes for user interaction
int getChoice(drink[]);
void transaction(drink[], int, double&);

int main()
{
    const int NUM_DRINKS = 5; // Total drink count
    drink drinks[NUM_DRINKS]= {
                                    {"Cola",0.75,20},
                                    {"Root Beer",0.75,20},
                                    {"Lemon-Lime",0.75,20},
                                    {"Grape Soda",0.80,20},
                                    {"Cream Soda",0.80,20}
                              };
    int choice; double payment;

    cout << "Make a drink selection: " << endl;
    for (int i = 0 ; i < NUM_DRINKS ; i++)
    {
        cout << drinks[i].flavor << " is $" << drinks[i].cost << endl;
    }

    choice = getChoice(drinks);   // Get the users drink choice and set it to the variable "choice"
    
    cout << "That drink costs $" << drinks[choice].cost << endl;
    cout << "Please enter your payment: ";
   /* 
    transaction (drinks, choice, payment);
    commented out, as any variation of this function call leads to compile time errors
    */

    cout << endl << "Please come again!" << endl;

    return 0;
}

int getChoice(drink[])
{
    int choice;
    do
    {
        cout << "Please make a selection by entering a number 0-4: ";
        cin >> choice;
        
    }while((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4));   // Ensure the selection is legal
    
    return choice;
}

void transaction(drink drink[], int choice, double payment)
{
    cout << "The cost of your selection was: $" << drink[choice].cost << endl;
    cout << "Please enter payment, only denominations less than $1.00: ";
    do
    {
        cin >> payment;

    }while((payment > 1.00) && (payment != drink[choice].cost));
    drink[choice].inv =- 1;
    cout << "Only " << drink[choice].inv << " of that choice remaining.";
}


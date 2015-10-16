// The pseudocode plan for assignment 4
// This needs to simulate a vending machine
#include <iostream>
#include <string>

int getChoice(Drink []);
void transaction(Drink [], int, double &);

struct drinks
{
    string flavor;      // Holds the flavor of the drink
    float cost;         // Holds the cost of each drink
    int inv;            // Number of drinks in the machine
};

int main()
{
    drinks cola = { "Cola", 0.75, 20 };
    drinks rb = { "Root Beer", 0.75, 20 };
    drinks ll = { "Lemon-Lime", 0.75, 20 };
    drinks gs = { "Grape Soda", 0.80, 20 };
    drinks cs = { "Cream Soda", 0.80, 20 };
    int choice, pay;

    const int NUM_DRINKS = 5; // Total drink count
    drinks[] = { cola, rb, ll, gs, cs } // setup the array of drinks in the machine
    
    cout << "Make a drink selection: " << endl;
    // Run a for loop to display the drink options
    getChoice (drinks[]);   // Get the users drink choice
    
    cout << "That drink costs $" << drinks[choice].cost << endl;
    cout << "Please enter your payment: ";
    transaciton (drinks [], int double &);
    
    cout << "Please come again!" << endl;

}

int getChoice(Drink [])
{
    // Get the users choice and use it to select an option from the array
}

void transaction(Drink [], int, double &)
{
    // Have the user pay for their drink choice
}

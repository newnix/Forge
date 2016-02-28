// Practice Program 10-23
// Allows the user to enter a number
// Then converts the number to a dollar amount

#include <iostream>
#include <string>

// Function prototype
void dollarFormat(std::string &);

int maint()
{
    std::string input;

    // Get the dollar amount from the user
    std::cout << "Enter a dollar amount in the form nnnnn.nn : ";
    std::cin >> input;
    dollarFormat(input);
    std::cout << "Here is the amount formatted: \n";
    std::cout << input << std::endl;
    
    return 0;
}

// Defining the dollarFormat function
// This function accepts a string reference object,
// Which assumes a number with a decimal point. 

void dollarFormat(std::string &currency)
{
    int dp;

    dp = curreny.find('.'); // Find the decimal point
    if (dp > 3)
    {
        for (int x = dp - 3; x > 0; x -= 3)
            string::currency.insert(x, ",");

    }
    currency.insert(0, "$");    // Insert the dollar sign
}

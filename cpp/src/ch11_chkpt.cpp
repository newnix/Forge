// Chapter 11 checkpoint practice program assignments
// Completing code fragments to solidify the concept

/*
 * These are the fragments that need to be completed:
 *
 * 11.1: Data structure to hold savings account information, needs
 * Account number (string object)
 * Account balance (double)
 * Interest rate (double)
 * Average monthly balance (double)
 *
 * 11.2: Write a definition statement for the variable in 11.1, initialize it with the following
 * Account Number: ACZ42137-B12-7
 * Account balance: $4512.59
 * Interest rate: 4%
 * Average monthly balance: $4217.07
 *
 * 11.3 Complete the following skeleton program using the structure outline to get
 * Name of movie
 * Name of the movie director
 * Name of the movie producer
 * Year the movie was released
 *
 * the skeleton program follows
 * #include <iostream>
 * using namespace std:
 *
 * // Write the structure declaration here
 * int main()
 * {
 *      cout << "Enter the following data about your\n";
 *      cout << "favorite movie.\n";
 *      cout << "name: ";
 *      // User entry
 *      cout << "Director: ";
 *      // User entry
 *      cout << "Producer: ";
 *      // User entry
 *      cout << "Release Year: ";
 *      //User entry
 *      cout << "Here's the data on your favorite movie:\n";
 *      // Display the user's input
 *      return 0;
 * }
 */

// Starting with 11.1
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct bankAcc
{
    string accountNum;  // Hold the account number
    double acctBal;     // Hold the account balance
    double interest;    // Hold the interest rate
    double monthlyBal;  // Hold the monthly account balance
};

struct favMov
{
    string name;    // Movie name
    string dir;     // Movie director
    string prod;    // Movie producer
    string rel;     // Movie release year
};

int main()
{
    bankAcc acc1 = {"ACZ42137-B12-7", 4512.59, 4, 4217.07};
    favMov mov;

    // Print the account info to stdout
    cout << "This part of the program uses a pre-initialized structure to output data." << endl << endl;
    cout << "This is the account info for Account 1." << endl;
    cout << fixed << showpoint << setprecision(2);
    cout << "Account: " << acc1.accountNum << endl;
    cout << "Balance: $" << acc1.acctBal << endl;
    cout << "Interest: %" << acc1.interest << endl;
    cout << "Average monthly balance: $" << acc1.monthlyBal << endl << endl;
    
    // Starting on the 11.3 skeleton program
    cout << endl << endl;
    cout << "This part of the program collects information about the users favorite movie to initialize and output a data structure."
         << endl << endl;
    cout << "Enter the following about your favorite movie." << endl;
    cout << "Movie title: ";
    getline(cin, mov.name);
    cout << "Director: ";
    getline(cin, mov.dir);
    cout << "Producer: ";
    getline(cin, mov.prod);
    cout << "Release Year: ";
    getline(cin, mov.rel);
    cout << "The movie data collected is as follows: \n";
    cout << "Title: " << mov.name << endl;
    cout << "Directed by: " << mov.dir << endl;
    cout << "Produced by: " << mov.prod << endl;
    cout << "Released in: " << mov.rel << endl;

    return 0;
}

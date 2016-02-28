// Implementation file for the dateTime class
// found on page 931

#include <iostream>
#include <string>
#include "dateTime.h"

using namespace std;

/*
 * Default constructor
 * Note that this constructor does nothing more than call
 * the date and time default constructors
 */

dateTime::dateTime() : date(), time()
{
    // Intentionally left without any functions, just run the default constructors.
}

/*
 * Constructor
 * Note that this only calls the base class constructors
 * it runs no additional functions or adds any additional data
 */

dateTime::dateTime(int d, int m, int y, int hr, int mi, int se) : date(d, m, y), time(hr, mi, se)
{
    // Still doing nothing important in here.
}

/*
 * The showDateTime member function 
 * displays the date and the time
 */

void dateTime::showDateTime() const
{
    // Display the date in the form mm/dd/yyyy
    cout << getMonth() << "/" << getDay() << "/" << getYear() << " ";

    // Display the time in the form hh:mm:ss
    cout << getHour() << ":" << getMin() << ":" << getSec() << endl;
}

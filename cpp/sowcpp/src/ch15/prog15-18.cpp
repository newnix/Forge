// Practice program 15-18
// found on page 932
// THis program displays a class with multiple inheritance

#include "dateTime.h"

using namespace std;

int main()
{
    // Define a dateTime object and use the default constructor to initialize it
    dateTime emptyDay;

    // Display the object's date and time
    emptyDay.showDateTime();

    // Define a dateTime object and initialize it
    dateTime pastDay(2, 4, 1960, 5, 32, 27);

    // Display that new object's date and time information
    pastDay.showDateTime();

    return 0;
}

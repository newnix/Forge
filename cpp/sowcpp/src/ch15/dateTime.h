// Specification file for dateTime class 
// used to exemplify multiple inheritance
// found on page 930

// Header guard
#ifndef DATETIME_H
#define DATETIME_H

#include "date.h"
#include "time.h"
#include <string>

using namespace std;

class dateTime : public date, public time
{
    public:
        // Default constructor
        dateTime();

        // Constructor
        dateTime(int, int, int, int, int, int);

        // The showDateTime
        // function displays the date and time
        void showDateTime() const;
};
#endif

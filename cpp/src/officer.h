// Police Officer class header
// This class holds the officer data
// And evaluates if a ticket is necessary

// Header guard
#ifndef OFFICER_H
#define OFFICER_H

#include "ticket.h"

class officer
{
    private:
        string name;    // Officer's name
        int badge;      // Officer's badge number
    public:
        // Constructor
        officer()
        {
            name = "John Smith";
            badge = 8675309;
        }

        // Setting new officer parameters
        void setName(string s)
            { name = s; }

        void setBadge(int b)
            { badge = b; }

        // Return the officer's data
        string getName() const
            { return name; }

        int getBadge() const
            { return badge; }
};
#endif

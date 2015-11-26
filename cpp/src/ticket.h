// Parking ticket class header
// Keeps track of how much the ticket is for, 
// and the properties of the car getting the ticket.

// Header guard
#ifndef TICKET_H
#define TICKET_H

// Pull in the car class properties
// and the meter properties
#include "car.h"
#include "meter.h"

class ticket
{
    private:
        float cost;              // Cost of the parking ticket
        const float RATE = 25;   // Base rate of the parking ticket costs
        const float aRATE = 10;  // Rate of the parking ticket after the initial hour
        
    public:
       float ticketCost(float meter.time, float car.time )
       {    
            float c;
            c = car.time - meter.time;
            if ( c > 0 )
            {
                if ( c > 60 )
                {
                    return ( ((c/60) * aRATE) + ((c%60) * aRATE) + RATE)
                }
            }
            else
            {
                return 0;
            }
        }
};
#endif

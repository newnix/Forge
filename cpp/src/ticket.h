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
        float cost; // Cost of the parking ticket
        const float RATE;   // Rate of the parking ticket costs
        
    public:
        


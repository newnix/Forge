// Parking meter class header
// This only keeps track of how long the car can stay

// Header guard
#ifndef METER_H
#define METER_H

class meter
{
    private:
        float time; // Time the car can be parked

    public:
        void setTime(float t)
            { time = t; }

        float getTime() const   // Return the time alloted, in minutes
            { return time; }
};
#define METER_H

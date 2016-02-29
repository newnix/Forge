// Practice program 09 from chapter 01
// Found on page 37
// Calculates the drop distance of an object based on drop time

#include <iostream>

double dm (float);   // Metric conversion
double de (float);   // Empirical conversion

int main()
{
    // set up the one variable we need
    float s;    // Seconds falling



}

// Calculate the distance dropped in meters
double dm(float sec)
{
    float acc = 9.8;
    return ((acc * sec * sec) / 2);
}

// Calculate the distance dropped in feet
double du(float sec)
{
    float acc = 32;
    return ((acc * sec * sec) / 2);
}

// Practice program 1 from chapter 2
// Found on page 102
// Converts metric tonnes to cereal boxes and such

#include <iostream>

// Forward declaration of the conversion functions
double mtonne(int,float);

double cerealb(double,float);

int main()
{
    // create the needed variables
    float oz;   // Ounces of cereal in a box
    int box;    // Number of boxes of cereal

    // Let the user know what's going on
    std::cout << "Hello, this program calculates how many boxes of cereal are needed to make a metric tonne of cereal and vice-versa.\n";
    

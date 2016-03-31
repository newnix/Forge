// Practice program 09 from chapter 01
// Found on page 37
// Calculates the drop distance of an object based on drop time

#include <iostream>

double dm (float);   // Metric conversion
double du (float);   // Empirical conversion

int main()
{
    // set up the one variable we need
    float s;    // Seconds falling
    
    // Set selection variables
    char pic;   // empirical or metric selection
    char go;    // new calculation

    // Let the user know what we're doing
    std::cout << "Hello, I'll calcuate the drop distance of an object given a time it's falling!\n";

    do
    {
        std::cout << "First, we'll need to determine if we're calculating things in metric units or empirical units.";
        std::cout << "\nFor metric units press \'m\', for empirical or US customary, press \'u\': ";
        std::cin >> pic;

        if (toupper(pic) == 'M')
        {
            std::cout << "\nEnter the time the object was falling: ";
            std::cin >> s;
            std::cout << "\nThe distance this object fell was " << dm(s) << " meters.\n";
        }

        else if (toupper(pic) == 'U')
        {
            std::cout << "\nEnter the time the object was falling: ";
            std::cin >> s;
            std::cout << "\nThe distance this object fell was " << du(s) << " feet.\n";
        }

        else
        {
            std::cout << "\nThat was not a valid entry, do you want to leave? [Y/N]";
            std::cin >> go;
        }
        
        std::cout << "\nWould you like to run another calculation? [Y/N] ";
        std::cin >> go;

    }while(toupper(go) == 'Y');

    return 0;

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

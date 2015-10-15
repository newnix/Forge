// This is the practice program 10-3 on p. 546
// Demonstrating the toupper() and tolower() functions in an input validation loop

#include <iostream>
#include <cctype>
#include <iomanip>

int main()
{
    const double PI = 3.14159;   // Constant value of pi
    double radius;      // The radius of a circle
    char goAgain;       // Holds a yes or no response

    std::cout << "This program calculates the area of a circle.\n";
    std::cout << std::fixed << std::setprecision(2);

    do
    {
        // Get the radius and display the area of the circle given that radius
        std::cout << "Enter the radius of the circle: " << std::endl;
        std::cin >> radius;
        std::cout << "\nThe area is " << (PI * radius * radius);
        std::cout << std::endl;

        // Discover if the user wants to run the program again
        std::cout << "Calculate the area of another circle? (Y/N)" << std::endl;
        std::cin >> goAgain;

        while (toupper(goAgain) != 'Y' && toupper(goAgain) != 'N')
        {
            std::cout << "Please enter 'Y' or 'N' : " << std::endl;
            std::cin >> goAgain;
        }
    }while (toupper(goAgain) == 'Y');

    return 0;
}

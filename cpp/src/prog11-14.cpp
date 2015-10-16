// Practice program 11-14 found on page 635
// Demonstrates using enumberated data types initialized to different values
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    enum Water { freezing = 0, boiling = 100 };
    int temp; // To hold the temp of the water

    cout << "Enter the current water temperature: ";
    cin >> temp;

    if (temp <= freezing )
    {
        cout << "The water is frozen." << endl;
    }
    else if (temp >= boiling)
    {
        cout << "The water is boiling." << endl;
    }
    else
    {
        cout << "The water is still a liquid, neither freezing nor boiling" << endl;
    }

    return 0;
}

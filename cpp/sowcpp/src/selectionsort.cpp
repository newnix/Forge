// This is an example of the selection sort algorithm, found on p. 471
// Array is sorted in ascending order
#include <iostream>
using namespace std;

// Function prototypes
void selectionSort(int [], int);
void showArray(const int [], int);

int main()
{
    // Define an array with unsorted values
    const int SIZE = 6;
    int values[SIZE] = {5,7,2,8,9,1};

    // Display the values (unsorted)
    cout << "The unsorted values are: \n";
    showArray(values, SIZE);

    // Sort the values
    selectionSort(values, SIZE);

    // Display the values again (sorted)
    cout << "The sorted values are: \n";
    showArray(values, SIZE);
    return 0;
}

// Definition of the function selectionSort
// This function performs an ascending order selection sort on the array
// size is the number of elements in the array

void selectionSort(int array[], int size)
{
    int startScan, minIndex, minValue;

    for (startScan = 0; startScan < (size -1); startScan++)
    {
        minIndex = startScan;
        minValue = array[startScan];
        for(int index = startScan + 1; index < size; index++)
        {
            if (array[index] < minValue)
            {
                minValue = array[index];
                minIndex = index;
            }
        }
        array[minIndex] = array[startScan];
        array[startScan] = minValue;
    }
    cout << "Total number of exchanges: " << startScan << endl;
}

// Definition of function showArray
// This function displays the contents of the array
// size is the number of elements in the array

void showArray(const int array[], int size)
{
    for (int count = 0; count < size; count++)
        cout << array[count] << " ";
    cout << endl;
}

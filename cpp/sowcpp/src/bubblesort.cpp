// This is an example of the bubbleSort function, found on p. 467
#include <iostream>
using namespace std;

// Function prototype
void sortArray(int [], int);
void showArray(const int [], int);

int main()
{
    // Array of unsorted values
    int values[6] = {7, 2, 3, 8, 9, 1};

    // Display the values
    cout << "The unsorted values are: \n";
    showArray(values, 6);

    // Sort the values
    sortArray(values, 6);

    // Display the values again, this time they're sorted
    cout << "The sorted values are: \n";
    showArray(values, 6);
    return 0;
}

// Definition of function sortArray
// This function performs an ascending order bubblesort on the array.
// size is the number of elements in the array

void sortArray(int array[], int size)
{
    bool swap;
    int temp;

    do
    {
        swap = false; 
        for (int count = 0; count < (size -1); count++)
        {
            if (array[count] > array[count + 1])
            {
                temp = array[count];
                array[count] = array[count + 1];
                array[count + 1] = temp;
                swap = true;
            }
            if (swap) == false
                cout << "Total exchanges: " << count << endl;
        }
    } while (swap);
}

// Definition of the funtion showArray
// This function displays the contents of array.
// Size is the number of elements

void showArray(const int array[], int size)
{
    for (int count = 0; count < size; count++)
        cout << array[count] << " ";
    cout << endl;
}


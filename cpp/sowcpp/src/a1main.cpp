// A1-Arrays
// Sorting Benchmarks, p. 488
// required function prototypes:
#include <iostream>

int bubbleSort(long [], int);
int selectionSort(long [], int);
void showArray(long [], int);

int main()
{
    // Create a singular array for both algorithms to sort
    int exchanges;
    const int SIZE = 25;

    // Set some values
    long sortList[SIZE] = {1,23,2,85,15,53,20,
                    30,8,75,4,96,12,35,
                    0,9,74,16,17,66,99,
                    500,235,144,123};
    // Display the sorted values and the number of exchanges for each method
    // Bubble Sort
    std::cout << "Calling Bubble Sort algorithm. . .\n";
    bubbleSort(sortList, SIZE);
    std::cout << "The sorted array is: ";
    showArray(sortList, SIZE);
    std::cout << "It took " << bubbleSort(sortList, SIZE) << " exchange operations to complete the sorting.\n\n";
    
    // Create a duplicate, unsorted Array
    long sortList2[SIZE] = {1,23,2,85,15,53,20,
                    30,8,75,4,96,12,35,
                    0,9,74,16,17,66,99,
                    500,235,144,123};

    // Selection Sort
   std::cout << "Calling Selection Sort algorithm. . .\n";
   selectionSort(sortList2, SIZE);
   std::cout << "The sorted array is: ";
   showArray(sortList2, SIZE);
   std::cout << "It took " << selectionSort(sortList2, SIZE) << " exchange operations to complete the sorting.\n\n";


    return 0;
}


int bubbleSort(long array[], int size)
{
    bool swap;
    int temp;
    int count;
    int exchanges;

    do
    {
        swap = false;
        for (count = 0; count < (size -1); count++)
        {
            if (array[count] > array[count + 1])
            {
                temp = array[count];
                array[count] = array[count + 1];
                array[count + 1] = temp;
                swap = true;
            }
        }
    }while (swap);
    exchanges = count;
    return exchanges;
}

int selectionSort(long array[], int size)
{
    int startScan, minIndex, minValue;

    for (startScan = 0; startScan < (size - 1); startScan++)
    {
        minIndex = startScan;
        minValue = array[startScan];
        for (int index = startScan + 1; index < size; index ++)
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
   return startScan;
}

void showArray(long array[], int size)
{
    for (int count = 0; count < size; count ++)
        std::cout << array[count] << " ";
    std::cout << std::endl;
}

// Attempting to calculate the mode of an array
// Written 2015.09.18 19:35

#include <iostream>

int mode( int *, int);

int main()
{
    int size = 10;
    int array[10] = { 1,2,2,2,3,4,7,8,9,10 };

    std::cout << "The mode of this array is: " << mode(array, size);
}

int mode(int *array, int size)
{
    int* ipRepetition = new int[size];
    for (int i = 0; i < size; i++)
    {
        ipRepetition[i]=0;
        int j = 0; 
        bool bFound = false;
        while ((j < i) && (array[i] != array[j]))
        {
            if (array[i] != array[j])
                j++;
        }
        ++(ipRepetition[j]);
    }
    int MaxRepeat = 0;
    for (int i = 1; i < size; i++)
    {
        if (ipRepetition[i] > ipRepetition[MaxRepeat])
            MaxRepeat =i;
    }
    delete [] ipRepetition;
    return array[MaxRepeat];
}

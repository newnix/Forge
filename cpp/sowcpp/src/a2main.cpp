// Assignment 2, Page 539, Movie statistics

#include <iostream>

double median(int *, int);
double mean(int *, int);
int mode(int *, int);
int *makeArray(int);
void getMovieData(int *, int);
void selectionSort(int [], int);

int main()
{
    std::cout << "How many students were in the research group? " << std::endl;
    int students;
    std::cin >> students;
    int *survey;
    // Create an array with the number of students surveyed defining the number of addresses
    survey = makeArray(students);
    
    // Fill the array with the data given by the students interviewed
    getMovieData(survey, students);
    
    // Sort the input so it can be used efficiently in the statistical functions
    selectionSort(survey, students);
    
    // Find the average amount of movies seen by each student
    std::cout << "\nThe average number of movies seen per student is: " << mean(survey, students) <<" movies.\n" << std::endl;

    std::cout << "\nThe most frequent number of movies seen was: " << mode(survey, students) << " movies per student.\n" << std::endl;

    std::cout << "\nThe median number of movies seen was: " << median(survey, students) << " movies per student.\n";
    return 0;

}

int *makeArray(int num)
{
    int *arr;
    
    //Ensure a valid array size
    if (num <= 0)
        return NULL;

    arr = new int[num];

    return arr;
}

void getMovieData(int *arr, int size)
{
    for (int count = 0; count < size; count ++)
    {
        std::cout << "Student " << (count + 1) << " saw how many movies? ";
        std::cin >> arr[count];
    }
}

void selectionSort(int array[], int size)
{
    int startScan, minIndex, minValue;

    for (startScan = 0; startScan < (size - 1); startScan++)
    {
        minIndex = startScan;
        minValue = array[startScan];
        for (int index = startScan + 1; index < size; index ++)
        {
            if(array[index] < minValue)
            {
                minValue = array[index];
                minIndex = index;
            }
        }
        array[minIndex] = array[startScan];
        array[startScan] = minValue;
    }
}

double mean(int *arr, int size)
{
    double avg;
    double total = 0.0;
    for(int count = 0; count < size; count ++)
    {
        total += arr[count];
    }
    avg = total / size;
    return avg;
}

int mode(int *arr, int size)
{
    int *repetition = new int[size];
    for (int count = 0; count < size; count++)
    {
        repetition[count]=0;
        int j = 0;
        bool found = false;
        while ((j < count) && (arr[count] != arr[j]))
        {
            if (arr[count] != arr[j])
                j++;
        }
        (repetition[j])++;
    }
    int maxRepeat = 0;
    for (int count = 1; count < size; count ++)
    {
        if (repetition[count] > repetition[maxRepeat])
            maxRepeat = count;
    }
    delete [] repetition;
    return arr[maxRepeat];
}

double median (int *arr, int size)
{
    double median = 0.0;
    if ((size % 2) ==0)
    {
        median = (arr[size/2] + arr[(size/2) - 1]) / 2.0;
    }
    else 
    {
        median = arr[size/2];
    }
    delete [] arr;
    return median;
}


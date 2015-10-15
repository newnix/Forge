// Binary search example found on p. 456
#include <iostream>
using namespace std;

// Function prototype
int binarySearch(const int [], int, int);
const int SIZE = 20;

int main()
{
	// Array with employee ids sorted in ascending order
	// Binary searches only work when the array is sorted
	int idNums[SIZE] = {101, 142, 147, 189, 199, 207, 222,
				234, 289, 296, 310, 319, 388,
				394, 417, 429, 447, 521, 536, 600};
	int results;	// To hold the search results
	int empID;	// To hold an employee ID

	// Get an Employee ID to search for
	cout << "Enter the employee ID you wish to search for: ";
	cin >> empID;

	// Search for the ID
	results = binarySearch(idNums, SIZE, empID);

	// If results contains -1 the ID was not found
	if (results == -1)
		cout << "That number does not exist in the array.\n";
	else
	{
		// Otherwise results contains the subscript
		// of the specified employee ID in the array
		cout << "That ID is found at element " << results;
		cout << " in the array.\n";
	}
	return 0;
}

// The binarySearch function performs a binary search on an int array.
// array, which has a max size of elements, is searched for the number stored in value.
// If the number is found, its array subscript is return, else -1 is returned, 
// indicating the value does not exist in the array

int binarySearch(const int array[], int size, int value)
{
	int first = 0,		// First array element
	last = size - 1,	// Last array element
	middle,			// Midpoint of search 
	position = -1;		// Position of search value
	bool found = false;	// Flag

	while (!found && first <= last)
	{
		middle = (first + last) / 2;	// Calculate midpoint
		if (array[middle] == value)	// If value is found at mid
		{
			found = true;
			position = middle;
		}
		else if (array[middle] > value)	// If value is in lower half
			last = middle - 1;
		else
			first = middle + 1;	// If value is in upper half
	}
	return position;
}

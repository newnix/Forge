// Specification file for the student class
// found on page 922

// Header guard
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class student
{
    protected:
        string name;    // Name of the student
        string id;      // Student ID number
        int year;       // Year student was admitted

    public:
        // Default constructor
        student()
        {
            name = " ";
            id = " ";
            year = 0;
        }

        // Constructor
        student(string n, string i, int y)
        {
            set(n, i, y);
        }

        // The set function sets the attribute data
        void set(string n, string i, int y)
        {
            name = n;
            id = i;
            year = y;
        }

        // Accessor functions
        string getName() const
        {
            return name;
        }

        string getID() const
        {
            return id;
        }

        int getYear() const
        {
            return year;
        }

        // Pure virtual function
        virtual int getRemainingHours() const = 0;
};
#endif

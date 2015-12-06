// Specification for the date class
// used to exemplify multiple inheritance 
// found on page 928

// Header guard
#ifndef DATE_H
#define DATE_H

class date
{
    protected:
        int day;
        int month;
        int year;
    public:
        // Default constructor
        date()
        {
            day = 01;
            month = 01;
            year = 1970;
        }

        // Constructor
        date(int d, int m, int y)
        {
            day = d;
            month = m;
            year = y;
        }

        // Accesors
        int getDay() const
        {
            return day;
        }

        int getMonth() const
        {
            return month;
        }

        int getYear() const
        {
            return year;
        }
};
#endif

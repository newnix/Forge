// Specification for the time class
// used to exemplify multiple inheritance
// found on page 929

// Header guard
#ifndef TIME_H
#define TIME_H

class time
{
    protected:
        int hour;
        int min;
        int sec;
    public:
        // Default constructor
        time()
        {
            hour = 0;
            min = 0;
            sec = 0;
        }

        // Constructor
        time(int h, int m, int s)
        {
            hour = h;
            min = m;
            sec = s;
        }

        // Accessor functions
        int getHour() const
        {
            return hour;
        }

        int getMin() const
        {
            return min;
        }

        int getSec() const
        {
            return sec;
        }
};
#endif

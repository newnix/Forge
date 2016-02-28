// Rectangle header file version 4
// found on page 743
// contains necessary modifications for prog 14-5

#ifndef RECTANGLE_H
#define RECTANGLE_H

class rectangle
{
    private:
        double width;
        double length;
    public:
        rectangle(double w, double l)  // Constructor
            { width = w; length = l; }  // set the initial conditions for the rectangle

        void setw(double w)
            { if ( w > 0) width = w; }  // set the width after performing sanity check

        void setl(double l)
            { if ( l > 0) length = l; }  // set the length after performing sanity check

        double getw() const
            { return width; }    // return the width

        double getl() const
            { return length; }  // return the length

        double geta() const
            { return (length * width); }    // returns the area
};
#endif

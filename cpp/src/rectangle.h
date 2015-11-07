// Rectangle header file
// This should keep me from having to redefine rectangle objects

// Header guard, make sure the code doesn't get duplicated
#ifndef RECTANGLE_H

#define RECTANGLE_H

class rectangle
{
    private:
        double width;
        double length;
    public:
        void setw(double);
        void setl(double);
        double getw() const;
        double getl() const;
        double geta() const;
        rectangle();
};

/*
 * define the constructor rectangle()
 */

rectangle::rectangle()
{
    width = 0.0;
    length = 0.0;
}

/*
 * define setw, which sets the rectangle width
 */

void rectangle::setw(double w)
{
    width = w;
}

/*
 * define setl, which sets the rectangle length
 */

void rectangle::setl(double l)
{
    length = l;
}

/*
 * getw returns the width of the object
 */

double rectangle::getw() const
{
    return width;
}

/*
 * getl returns the length of the object
 */

double rectangle::getl() const
{
    return length;
}

/*
 * geta returns the area of the rectangle
 */

double rectangle::geta() const
{
    return length * width;
}

#endif

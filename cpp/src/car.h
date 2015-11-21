// Car class header
// Keeps track of car attributes

// Make sure there's only one copy of the header
// pulled into the source file
#ifndef CAR_H
#define CAR_H

#include <string>

class car
(
    private:
        string make;    // Make of the car
        string model;   // Model of the car
        string color;   // Color of the car
        string plate;   // License plate of the car
        float time;     // Time the car's been parked

    public:

    // Constructor
        car(string ma, string mo, string c, string p, float t)
        {
            make = ma;
            model = mo;
            color = c;
            plate = p;
            time = 0.0;
        }

    // Destructor
        ~car()
        {
            delete [] car;
        }


    // Void functions, set the car variables
        void setMake(string m)
            { make = m; }

        void setModel(string m)
            { model = m; }

        void setColor(string c)
            { color = c; }

        void setPlate(string p)
            { plate = p; }

        void setTime(float t)
            { time = t; }

    // Return the car parameters
        string getMake() const
        {
            return make;
        }

        string getModel() const
        {
            return model;
        }

        string getColor() const
        {
            return color;
        }
        
        string getPlate() const
        {
            return plate;
        }

        float getTime() const
        {
            return time;
        }
};
#endif

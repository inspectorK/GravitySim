#pragma once

/*

vect represents a vector as the combination of x and y components.  This allows the vect class
to easily double as both a position (x,y) or vel/acc.  Functions are used to calculate the 
magnitude or angle for the given x,y.

*/

class vect
{
    friend class particle;
private:
    // Simulation data members
    double _x;                                              // x component
    double _y;                                              // y component

public:
    // Constructors
    vect();
    vect(double, double);

    // Helpers
    void print() const;

    // Getters
    double get_x() const;
    double get_y() const;
    double get_magnitude() const;
    double get_angle() const;                               // radians
    vect get_unitvector() const;                            // get unit vector in same direction as this

    // Setters
    void setx(double);
    void sety(double);
    void set_magnitude(double);                             // set magnitude while preserving angle
    void set_angle(double);                                 // set angle while preserving magnitude
    void reset(double, double);                             // update vect _x and _y directly

    // Operator Overloads
    vect operator+(const vect& other);
    vect operator-(const vect& other);
    vect operator*(const double& scalar);                   // scalar multiplication  TODO: cross product
    vect operator/(const double& scalar);                   // scalar division
    void operator=(const vect& other);                      // copy constructor
};


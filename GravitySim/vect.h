#pragma once
class vect
{
    friend class particle;
private:
    double _x;
    double _y;
public:
    // Constructors
    vect();
    vect(double, double);

    // Helpers
    void print() const;

    // Getters
    double get_x();
    double get_y();
    double get_magnitude() const;
    double get_angle() const;
    vect get_unitvector() const;

    // Setters
    void setx(double);
    void sety(double);
    void set_magnitude(double);
    void set_angle(double);
    void reset(double, double);

    // Operator Overloads
    vect operator+(const vect& other);
    vect operator-(const vect& other);
    vect operator*(const double& scalar);
    vect operator/(const double& scalar);
    void operator=(const vect& other);
};


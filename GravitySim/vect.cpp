#include "vect.h"
#include <cmath>
#include <iostream>

#pragma region Constructors

vect::vect()
{
    this->_x = 0;
    this->_y = 0;
}

vect::vect(double x, double y)
{
    this->_x = x;
    this->_y = y;
}

void vect::print() const
{
    std::cout << _x << "," << _y;
}

#pragma endregion

#pragma region Getters

double vect::get_x() const
{
    return _x;
}

double vect::get_y() const
{
    return _y;
}

double vect::get_magnitude() const
{
    // Returns the magnitude of vector via pythagorean theorem
    return sqrt(pow(_x, 2) + pow(_y, 2));
}

double vect::get_angle() const 
{

    return atan2(this->_y, this->_x);
}

vect vect::get_unitvector() const
{
    // construct, calculate, and return unit vector for this vector
    vect uvect;
    uvect.setx(this->_x / this->get_magnitude());
    uvect.sety(this->_y / this->get_magnitude());
    return uvect;
}

#pragma endregion

#pragma region Setters

void vect::setx(double newx)
{
    this->_x = newx;
}

void vect::sety(double newy)
{
    this->_y = newy;
}

void vect::set_magnitude(double newmagnitude)
{
    // break down magnitude into x and y components
    double newx = newmagnitude * cos(this->get_angle());
    double newy = newmagnitude * sin(this->get_angle());

    this->reset(newx, newy);
}

void vect::set_angle(double newangle)
{
    // angle must be in radians
    double magnitude = get_magnitude();
    double newx = cos(newangle) * magnitude;
    double newy = sin(newangle) * magnitude;

    this->reset(newx, newy);
}

void vect::reset(double x, double y)
{
    this->_x = x;
    this->_y = y;
}

#pragma endregion

#pragma region OperatorOverloads

vect vect::operator+(const vect& other)
{
    double newx = other._x + this->_x;
    double newy = other._y + this->_y;

    return vect(newx, newy);
}

vect vect::operator-(const vect& other)
{
    double newx = this->_x - other._x;
    double newy = this->_y - other._y;

    return vect(newx, newy);
}

vect vect::operator*(const double& scalar)
{
    double newx = this->_x * scalar;
    double newy = this->_y * scalar;
    return vect(newx, newy);
}

vect vect::operator/(const double& scalar)
{
    double newx = this->_x / scalar;
    double newy = this->_y / scalar;
    return vect(newx, newy);
}

void vect::operator=(const vect& other)
{
    this->_x = other._x;
    this->_y = other._y;
}

#pragma endregion

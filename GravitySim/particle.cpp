#include "particle.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>

#pragma region Constructors

particle::particle()
{
    _mass = 0;
    _pos = vect();
    _vel = vect();
    _id = next_available_id++;

    // colors
    _r = getRandomColor(false);
    _g = getRandomColor(false);
    _b = getRandomColor(false);
    _a = 0xff;
}

particle::particle(double m, double px, double py, double vx, double vy)
{
    _mass = m;
    _pos = vect(px, py);
    _vel = vect(vx, vy);
    _id = next_available_id++;

    // colors
    _r = getRandomColor(false);
    _g = getRandomColor(false);
    _b = getRandomColor(false);
    _a = 0xff;
}

particle::particle(double m, vect pos, vect vel)
{
    _mass = m;
    _pos = pos;
    _vel = vel;
    _id = next_available_id++;
}

#pragma endregion

#pragma region Getters

int particle::get_id() const
{
    return this->_id;
}

int particle::get_rendersize() const
{
    return _size;
}

double particle::get_mass() const
{
    return _mass;
}

double particle::get_distaceTo(particle other) const
{
    double dx = other._pos._x - this->_pos._x;
    double dy = other._pos._y - this->_pos._y;
    return sqrt(pow(dx, 2) + pow(dy, 2));
}

double particle::get_angleTo(particle other) const
{
    return atan2(other._pos._y - this->_pos._y, other._pos._x - this->_pos._x);
}

vect particle::get_position() const
{
    return _pos;
}

vect particle::get_velocity() const
{
    return _vel;
}

Uint8 particle::get_r() const
{
    return _r;
}

Uint8 particle::get_g() const
{
    return _g;
}

Uint8 particle::get_b() const
{
    return _b;
}

Uint8 particle::get_a() const
{
    return _a;
}

#pragma endregion

#pragma region Setters

void particle::set_mass(double m)
{
    _mass = m;
}

void particle::set_size(int size)
{
    this->_size = size;
}

void particle::set_position(double x, double y)
{
    vect temp = vect(x, y);
    this->_pos = temp;
}

void particle::set_velocity(double x1, double x2, double y1, double y2)
{
    vect temp = vect();
    temp.setx(x2 - x1);
    temp.sety(y2 - y1);
    this->_vel = temp;
}

#pragma endregion

#pragma region SimulationMethods

void particle::update_pos()
{
    this->_pos = this->_vel + this->_pos;
}

void particle::update_vel(particle other)
{
    this->_vel = this->_vel + calc_gTo(other);
}

vect particle::calc_gTo(particle other)
{
    vect g = vect();
    double d = get_distaceTo(other);

    // thanks newton
    g.set_magnitude(other.get_mass() / pow(d, 2));
    g.set_angle(this->get_angleTo(other));
    return g;
}

#pragma endregion

#pragma region HelperMethods

//  Function getRandomColor()
//
//  Param: bool rnd
//  rnd = true, return random color
//  rnd = false, return default white
Uint8 particle::getRandomColor(bool rnd)
{
    if (!rnd)
    {
        // return max value for white
        return 0xff;
    }
    srand(time(NULL));

    Uint8 color = rand() % 255;
    return color;
}

#pragma endregion
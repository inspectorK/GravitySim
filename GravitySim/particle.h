#pragma once
#include "vect.h"

#include <include/SDL/SDL.h>

class particle
{
private:
    double _mass;
    vect _pos;
    vect _vel;
    int _id;
    int _rendersize;
    static int next_available_id;

    // Color members
    Uint8 _r;
    Uint8 _g;
    Uint8 _b;
    Uint8 _a;

public:
    // Public Members

    // Constructors
    particle();
    particle(double x, double x1, double y1, double x2, double y2);
    particle(double x, vect pos, vect vel);

    // Getters
    int get_id() const;
    int get_rendersize() const;
    double get_mass() const;
    double get_distaceTo(particle other);
    double get_angleTo(particle other);
    vect get_position();
    vect get_velocity();
    Uint8 get_r();
    Uint8 get_g();
    Uint8 get_b();
    Uint8 get_a();

    // Setters
    void set_mass(double m);
    void set_rendersize(int size);
    void set_position(double x, double y);
    void set_velocity(double x1, double x2, double y1, double y2);

    // Simulation Methods
    void update_pos();
    void apply_g(particle other);
    vect calc_gTo(particle other);
    Uint8 getRandomColor(bool rand);

};

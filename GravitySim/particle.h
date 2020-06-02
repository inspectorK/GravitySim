#pragma once
#include "vect.h"
class particle
{
private:
    double _mass;
    vect _pos;
    vect _vel;
    int _id;
    static int next_available_id;

public:
    // Public Members

    // Constructors
    particle();
    particle(double x, double x1, double y1, double x2, double y2);
    particle(double x, vect pos, vect vel);

    // Getters
    int get_id() const;
    double get_mass() const;
    double get_distaceTo(particle other);
    double get_angleTo(particle other);
    vect get_position();
    vect get_velocity();

    // Setters
    void set_mass(double m);
    void set_position(double x, double y);
    void set_velocity(double x1, double x2, double y1, double y2);

    // Simulation Methods
    void update_pos();
    void apply_g(particle other);
    vect calc_gTo(particle other);

};

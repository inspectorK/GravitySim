/*

particle represents a single particle involved in the nbody simulation.  Every particle in the simulation
will influence every other particle.

*/

#pragma once
#include "vect.h"

#include <include/SDL/SDL.h>

class particle
{
private:
    // Simulation data members
    double _mass;
    vect _pos;                                      // vect represents coordinates of position
    vect _vel;                                      // vect represents x/y components of vel from pos
    int _id;                                        // incremented particle id (should be unique)
    static int next_available_id;

    // Graphics data members
    int _size;                                      // size of particle on screen (pixels)

    // Color members for SDL rendering
    Uint8 _r;                                       // red
    Uint8 _g;                                       // green
    Uint8 _b;                                       // blue
    Uint8 _a;                                       // alpha

public:
    // Constructors
    particle();
    particle(double m, double x1, double y1, double x2, double y2);
    particle(double m, vect pos, vect vel);

    // Getters
    int get_id() const;
    int get_rendersize() const;
    double get_mass() const;
    double get_distaceTo(particle other) const;
    double get_angleTo(particle other) const;
    vect get_position() const;
    vect get_velocity() const;
    Uint8 get_r() const;
    Uint8 get_g() const;
    Uint8 get_b() const;
    Uint8 get_a() const;

    // Setters
    void set_mass(double m);
    void set_size(int size);
    void set_position(double x, double y);
    void set_velocity(double x1, double x2, double y1, double y2);

    // Simulation Methods
    void update_pos();
    void update_vel(particle other);
    vect calc_gTo(particle other);

    // Helper Methods
    Uint8 getRandomColor(bool rand);

};

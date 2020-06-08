#pragma once

#include "vect.h"
#include "particle.h"
#include <iostream>

void run_particleUnitTest()
{
    vect pos1 = vect(0, 0);
    vect vel1 = vect(1, 0);
    particle moon = particle(1, pos1, vel1);

    vect pos2 = vect(10, 10);
    vect vel2 = vect(-1, 0);
    particle planet(1, pos2, vel2);

    // output initial position
    planet.get_position().print();
    std::cout << "\n";
    for (int iter = 0; iter < 100; iter++)
    {
        planet.update_vel(moon);
        planet.update_pos();
        planet.get_position().print();
        std::cout << "\n";
    }
}

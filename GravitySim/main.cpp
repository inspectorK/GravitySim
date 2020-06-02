#include "vect.h"
#include "vect_unittest.h"
#include "particle.h"
#include "simmgr.h"
#include <iostream>

int particle::next_available_id = 0;

int main(int argc, char* argv[])
{
    //vect pos1 = vect(0, 0);
    //vect vel1 = vect(0, 0);
    //particle sun = particle(50, pos1, vel1);

    //vect pos2 = vect(20, 20);
    //vect vel2 = vect(-2, 0);
    //particle planet(1, pos2, vel2);

    vector<particle> particles = vector<particle>();
    //particles.push_back(sun);
    //particles.push_back(planet);

    simmgr SimMgr = simmgr();
    SimMgr.sim_init(particles);
    SimMgr.run();
    

    return 0;
}
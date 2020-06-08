#include "vect.h"
#include "vect_unittest.h"
#include "particle.h"
#include "simmgr.h"
#include <iostream>

int particle::next_available_id = 0;

int main(int argc, char* argv[])
{
    bool sun = true;
    if (argc > 1)
    {
        if (argv[1] == "-sun")
        {
            sun = true;
        }
    }

    vector<particle> particles = vector<particle>();

    simmgr SimMgr = simmgr();
    SimMgr.sim_init(particles);
    SimMgr.run(sun);
    

    return 0;
}
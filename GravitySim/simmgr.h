/*

simmgr is the top level class that manages the nbody simulation

*/

#pragma once
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "vect.h"
#include "particle.h"

#include <include/SDL/SDL.h>
#include <include/GL/glew.h>

using namespace std;

const double PI = 3.14159265;

enum class sim_state
{
    initialize = 0,
    createobjects = 1,
    run = 2
};

class simmgr
{
private:
    // SDL Graphics Members
    SDL_Window* _window;                               // SDL window for simulation presentation
    SDL_Renderer* _renderer;                           // SDL renderer for various objects

    // Sim Members
    vector<particle> _particles;                       // internal "array" (vector is poor word choice) of particles involved in sim
    int _numparticles;                                 // number of particles within _particles
    int _numsteps;                                     // number of timesteps to execute
    sim_state _simstate;                               // internal simulation state

    // for user creating particles
    int _xdown;
    int _ydown;

    // Simulation Functions
    void print(int step);
    void execute_timestep(particle* p);
    double getDistanceBetweenPoints(int x1, int x2, int y1, int y2);        // TODO do we really need these?
    double getAngleBetweenPoints(int x1, int x2, int y1, int y2);           // TODO do we really need these?

    // Graphics Functions
    void sdl_printerrorifbad(int status);
    int sdl_init();                                     // initialize SDL library                        
    int sdl_windowinit();                               // initialize SDL window
    int sdl_rendererinit();                             // initialize SDL renderer
    vect sdl_getwindowcenter();                         // get center coordinates of SDL window

    void createobjects();                               // handles user creation of particles
    void processinput();                                // handles SDL events/input for creating particles
    
    // TODO: Currently need two drawParticle methods.  Particle is "created" currently on down click,
    //       but the object is not created until the upclick.  Need to handle this better
    void drawParticle(vect pos, int size);
    void drawParticle(particle p);
    void drawParticles(particle* particles);

public:
    // Constructors
    simmgr();
    simmgr(int numsteps);

    // Functions
    int sim_init(vector<particle> particles);
    void run(bool sun);

};


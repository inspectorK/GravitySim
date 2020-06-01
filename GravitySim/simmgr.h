#pragma once
#include <Windows.h>
#include <vector>

#include "vect.h"
#include "particle.h"
#include "status.h"

#include <include/SDL/SDL.h>
#include <include/GL/glew.h>

using namespace std;

class simmgr
{
private:
    // Members
    SDL_Window* _window;
    vector<particle> _particles;
    int _numparticles;
    int _numsteps;
    sim_state _simstate;

    int _xdown; // x coordinate of up click
    int _ydown; // y coordinate of down click 

    // Functions
    void execute_timestep(particle* p);
    void print();
    double getDistanceBetweenPoints(int x1, int x2, int y1, int y2);

public:
    // Constructors
    simmgr();
    simmgr(int numsteps);

    // Functions
    int sim_init(vector<particle> particles);

    // SDL related functions and handlers
    void sdl_printerrorifbad(int status);
    int sdl_init();
    int sdl_windowinit();
    void createobjects();
    void processinput();
    void run();

};


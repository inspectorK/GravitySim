#pragma once
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "vect.h"
#include "particle.h"
#include "status.h"

#include <include/SDL/SDL.h>
#include <include/GL/glew.h>

using namespace std;

const double PI = 3.14159265;

class simmgr
{
private:
    // SDL Members
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    // Sim Members
    vector<particle> _particles;
    int _numparticles;
    int _numsteps;
    sim_state _simstate;

    int _xdown; // x coordinate of up click
    int _ydown; // y coordinate of down click 

    // Functions
    void execute_timestep(particle* p);
    void print(int step);
    double getDistanceBetweenPoints(int x1, int x2, int y1, int y2);
    double getAngleBetweenPoints(int x1, int x2, int y1, int y2);

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
    int sdl_rendererinit();
    vect sdl_getwindowcenter();
    void createobjects();
    void processinput();
    void drawParticle(vect pos, int size);
    void drawParticle(particle p);
    void drawParticles(particle* particles);
    

    // Main run function
    void run(bool sun);

};


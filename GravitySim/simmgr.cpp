/*

simmgr is the top level class that manages the nbody simulation

*/

#include "simmgr.h"
#include <iostream>
#include <iomanip>
#include <cmath>

#define DEFAULT_TIMESTEPS 100

// SDL Window Default Options
const int WindowSizeX = 640;
const int WindowSizeY = 480;
const int SDLWindowOptions = SDL_WINDOW_SHOWN 
                           | SDL_WINDOW_RESIZABLE 
                           | SDL_WINDOW_OPENGL;

simmgr::simmgr()
{
    // just default to 100 steps
    _particles = vector<particle>();
    _numparticles = 0;
    _numsteps = DEFAULT_TIMESTEPS;
    _window = nullptr;
    _simstate = sim_state::initialize;
    _xdown = 0;
    _ydown = 0;
}

simmgr::simmgr(int numsteps)
{
    _particles = vector<particle>();
    _numparticles = 0;
    _numsteps = numsteps;
    _window = nullptr;
    _simstate = sim_state::initialize;
    _xdown = 0;
    _ydown = 0;
}

int simmgr::sim_init(vector<particle> particles)
{
    // build vector of particles
    _particles = particles;
    _numparticles = _particles.size();

    // initialize SDL
    int status = 0;
    status = sdl_init();
    if (status) { return status; }

    // if we get here we are good, return
    // _simstatus will be updated when run() is called

    return 0;
}

void simmgr::sdl_printerrorifbad(int status)
{
    if (status)
    {
        std::cout << "Error [" << status << "] " << SDL_GetError();
    }
}

int simmgr::sdl_init()
{
    // init SDL
    int status = SDL_Init(SDL_INIT_EVERYTHING);
    sdl_printerrorifbad(status);

    // init Window
    status = sdl_windowinit();
    sdl_printerrorifbad(status);
    return 0;
}

int simmgr::sdl_windowinit()
{
    _window = SDL_CreateWindow("GravitySim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowSizeX, WindowSizeY, SDLWindowOptions);
    if (!_window)
    {
        cout << "Error creating window.\n";
        return 1;
    }
    return 0;
}

void simmgr::createobjects()
{
    while (_simstate == sim_state::createobjects)
    {
        processinput();
    }
}

void simmgr::processinput()
{
    // locals
    SDL_Event evnt;
    bool priorDownEvent = false;
    double d = 0;
    double a = 0;

    while (SDL_PollEvent(&evnt))
    {
        switch (evnt.type)
        {
        case (SDL_QUIT):
            _simstate = sim_state::run;
            break;
        case (SDL_MOUSEBUTTONDOWN):
            std::cout << "Particle marked: " << evnt.button.x << "," << evnt.button.y << "\n";
            _xdown = evnt.button.x;
            _ydown = evnt.button.y;
            priorDownEvent = true;
            break;
        case (SDL_MOUSEBUTTONUP):
            d = getDistanceBetweenPoints(evnt.button.x, _xdown, evnt.button.y, _ydown);
            a = getAngleBetweenPoints(_xdown, evnt.button.x, _ydown, evnt.button.y) * 180.0 / PI;
            std::cout << "Particle end marked: " << evnt.button.x << "," << evnt.button.y 
                        << " Distance: " << d << " Velocity: " << (int)d/(int)10 << " Angle: " << a << "\n";
            // clear downEvent and locals
            priorDownEvent = false;
            _xdown = 0;
            _ydown = 0;
            break;

        default:
            continue;
        }
    }
}

void simmgr::run()
{
    if (_simstate != sim_state::initialize)
    {
        cout << "ERROR: Out of sequence call to run().  _simstate should be initialize()\n";
        return;
    }

    // on to next state, user will create objects to simulate
    _simstate = sim_state::createobjects;

    createobjects();

    // print intial condition
    print();

    // loop for the set number of timesteps
    for (int step = 0; step < _numsteps; step++)
    {
        // for each particle calculate forces
        for (int iter = 0; iter < _numparticles; iter++)
        {
            execute_timestep(&_particles[iter]);
        }

        // for each particle update positions
        for (int iter = 0; iter < _numparticles; iter++)
        {
            _particles[iter].update_pos();
        }
        print();
    }
}

void simmgr::execute_timestep(particle *p)
{
    // calculate and sum g force from all other particles
    for (int iter = 0; iter < _numparticles; iter++)
    {
        // skip over ourself
        if (p->get_id() == _particles[iter].get_id())
            continue;

        p->apply_g(_particles[iter]);
    }
    // wait until all forces are accounted for before calling update_pos()
    // p->update_pos();
}

void simmgr::print()
{
    // print header
    std::cout << "    mass   position" << "\n";
    std::cout << "    ----   --------" << "\n";
    // print status for all particles
    for (int iter = 0; iter < _numparticles; iter++)
    {
        std::cout << "p" << iter + 1 << ": " << std::setw(4) << _particles[iter].get_mass() << "   ";
        _particles[iter].get_position().print();
        std::cout << "\n";
    }
}

double simmgr::getDistanceBetweenPoints(int x1, int x2, int y1, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt(pow(dx, 2) + pow(dy, 2));
}

double simmgr::getAngleBetweenPoints(int x1, int x2, int y1, int y2)
{
    return atan2(y2 - y1, x2 - x1);
}

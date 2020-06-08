/*

particle represents a single particle involved in the nbody simulation.  Every particle in the simulation
will influence every other particle.

*/

#include "simmgr.h"
#include <iostream>
#include <iomanip>
#include <cmath>

#define DEFAULT_TIMESTEPS 1000

// SDL Window Default Options
const int SunMass = 5000;
const int SunSize = 20;
const int DefaultParticleSize = 6;
const int WindowSizeX = 1200;
const int WindowSizeY = 800;
const int SDLWindowOptions = SDL_WINDOW_SHOWN 
                           | SDL_WINDOW_RESIZABLE 
                           | SDL_WINDOW_OPENGL;

simmgr::simmgr()
{
    _particles = vector<particle>();
    _numparticles = 0;
    _numsteps = DEFAULT_TIMESTEPS;
    _window = nullptr;
    _renderer = nullptr;
    _simstate = sim_state::initialize;

    // for user creating particles
    _xdown = 0;
    _ydown = 0;
}

simmgr::simmgr(int numsteps)
{
    _particles = vector<particle>();
    _numparticles = 0;
    _numsteps = numsteps;
    _window = nullptr;
    _renderer = nullptr;
    _simstate = sim_state::initialize;

    // for user creating particles
    _xdown = 0;
    _ydown = 0;
}

int simmgr::sim_init(vector<particle> particles)
{
    // build vector of particles
    _particles = particles;

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

}

int simmgr::sdl_init()
{
    // init SDL
    int status = SDL_Init(SDL_INIT_EVERYTHING);
    if (status) { return 1; }

    // init Window
    status = sdl_windowinit();
    if (status) { return 1; }

    // init Renderer
    status = sdl_rendererinit();
    if (status) { return 1; }

    // set window color to black
    int stat = SDL_SetRenderDrawColor(_renderer, 0x0, 0x0, 0x0, 0xff);
    stat = SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
    return 0;
}

int simmgr::sdl_windowinit()
{
    _window = SDL_CreateWindow("GravitySim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowSizeX, WindowSizeY, SDLWindowOptions);
    if (!_window)
    {
        cout << "Error creating SDL_Window: " << SDL_GetError() << "\n";
        return 1;
    }
    return 0;
}

int simmgr::sdl_rendererinit()
{
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
    {
        cout << "Error creating SDL_Renderer: " << SDL_GetError() << "\n";
        return 1;
    }
    return 0;
}

vect simmgr::sdl_getwindowcenter()
{
    int x = WindowSizeX / 2;
    int y = WindowSizeY / 2;
    return vect(x, y);
    
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
    particle p = particle();
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
            drawParticle(vect(_xdown, _ydown), DefaultParticleSize);
            break;
        case (SDL_MOUSEBUTTONUP):
            p.set_mass(20);
            p.set_size(DefaultParticleSize);
            p.set_position(_xdown, _ydown);
            p.set_velocity(evnt.button.x / 10, _xdown / 10, evnt.button.y / 10, _ydown /10);
            _particles.push_back(p);
            d = getDistanceBetweenPoints(evnt.button.x, _xdown, evnt.button.y, _ydown);
            a = getAngleBetweenPoints(_xdown, evnt.button.x, _ydown, evnt.button.y) * 180.0 / PI;
            std::cout << "Particle end marked: " << evnt.button.x << "," << evnt.button.y 
                        << " Distance: " << d << " Velocity: " << (int)d/(int)10 << " Angle: " << a << "\n";
            // clear locals
            _xdown = 0;
            _ydown = 0;
            break;

        default:
            continue;
        }
    }
}

// Function: DrawParticle(vect, size)
// 
// Draws particle given a position vector and size.  Need this to render the particle
// on the down click.  Particle object not actually created until upclick
void simmgr::drawParticle(vect pos, int size)
{
    SDL_Rect particle;
    particle.x = pos.get_x() - size/2;
    particle.y = pos.get_y() - size/2;
    particle.h = size;
    particle.w = size;

    SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(_renderer, &particle);

    if (_simstate == sim_state::createobjects)
    {
        // only rerender here if we were initializing or user is drawing particles
        SDL_RenderPresent(_renderer);
    }
}

// Function: DrawParticle(particle)
//
// Draws the particle given a particle with the color defined in the object.  This should
// be the only method for drawing particles
void simmgr::drawParticle(particle p)
{
    SDL_Rect particle;
    particle.x = p.get_position().get_x() - p.get_rendersize()/2;
    particle.y = p.get_position().get_y() - p.get_rendersize()/2;
    particle.h = p.get_rendersize();
    particle.w = p.get_rendersize();

    SDL_SetRenderDrawColor(_renderer,
                           p.get_r(),
                           p.get_g(),
                           p.get_b(), 
                           p.get_a());
    SDL_RenderFillRect(_renderer, &particle);
    if (_simstate == sim_state::createobjects)
    {
        // only rerender here if we were initializing or user is drawing particles
        SDL_RenderPresent(_renderer);
    }

}

void simmgr::drawParticles(particle* particles)
{
    // TODO possible performance improvement with only a single render call to SDL render API?
}

void simmgr::run(bool sun)
{
    if (_simstate != sim_state::initialize)
    {
        cout << "ERROR: Out of sequence call to run().  _simstate should be initialize()\n";
        return;
    }

    // TODO this is ugly, do better
    if (sun)
    {
        // create massive particle at center of screen
        vect center = sdl_getwindowcenter();
        drawParticle(center, SunSize);
        particle sun = particle(SunMass, sdl_getwindowcenter(), vect(0, 0));
        sun.set_size(SunSize);
        _particles.push_back(sun);
    }

    // on to next state, user will create objects to simulate
    _simstate = sim_state::createobjects;

    createobjects();
    _numparticles = _particles.size();
    _simstate = sim_state::run;

    // print intial condition
    print(0);

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
            // since execute_timestep() nets all forces into the _vel vector, only need to update _pos once per particle
            _particles[iter].update_pos();
        }

        // set window color to black
        int stat = SDL_SetRenderDrawColor(_renderer, 0x0, 0x0, 0x0, 0xff);
        stat = SDL_RenderClear(_renderer);
        for (int iter = 0; iter < _numparticles; iter++)
        {
            // for each particle render the object to backbuffer
            drawParticle(_particles[iter]);
        }

        // publish backbuffer to window
        SDL_RenderPresent(_renderer);

        print(step);
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

        p->update_vel(_particles[iter]);
    }
    // wait until all forces are accounted for before calling update_pos()
    // p->update_pos();
}

void simmgr::print(int step)
{
    // print header
    std::cout << "    mass   position  step[" << step << "]\n";
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

/*

simmgr is the top level class that manages the nbody simulation

*/

#include "simmgr.h"
#include <iostream>
#include <iomanip>
#include <cmath>

#define DEFAULT_TIMESTEPS 100

// SDL Window Default Options
const int WindowSizeX = 1024;
const int WindowSizeY = 1024;
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
    _renderer = nullptr;
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
    _renderer = nullptr;
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
            drawParticle(evnt.button.x, evnt.button.y);
            break;
        case (SDL_MOUSEBUTTONUP):
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

void simmgr::drawParticle(int x, int y)
{
    SDL_Rect particle;
    particle.x = x;
    particle.y = y;
    particle.h = 8;
    particle.w = 8;

    SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(_renderer, &particle);
    SDL_RenderPresent(_renderer);
    
//    /* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
//   as expected by OpenGL for textures */
//    SDL_Surface* tempSurface = nullptr;
//    SDL_Texture* texture = nullptr;
//    Uint32 rmask, gmask, bmask, amask;
//
//    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
//       on the endianness (byte order) of the machine */
//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//    rmask = 0xff000000;
//    gmask = 0x00ff0000;
//    bmask = 0x0000ff00;
//    amask = 0x000000ff;
//    Uint32 pixelColor = 0;
//#else
//    rmask = 0x000000ff;
//    gmask = 0x0000ff00;
//    bmask = 0x00ff0000;
//    amask = 0xff000000;
//    Uint32 pixelColor = 0xff000000;
//#endif
//    if (!_renderer)
//    {
//        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//        if (!_renderer)
//        {
//            std::cout << "Error in SDL_CreateRenderer: " << SDL_GetError() << "\n";
//        }
//    }
//    tempSurface = SDL_CreateRGBSurface(0, 8, 8, 32, rmask, gmask, bmask, amask);
//    if (!tempSurface)
//    {
//        std::cout << "Error in SDL_CreateRGBSurface: " << SDL_GetError() << "\n";
//    }
//    texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
//    if (!texture)
//    {
//        std::cout << "Error in SDL_CreateTextureFromSurface: " << SDL_GetError() << "\n";
//    }
//    SDL_FreeSurface(tempSurface);
//
//    // allocate pixel buffer
//    Uint32* tempPixels = new Uint32[8 * 8];
//
//    // 0 init pixel buffer (0 will be black)
//    memset(tempPixels, 0, 8 * 8 * sizeof(Uint32));
//
//    // set pixel buffer with color
//    for (int iter = 0; iter < 8 * 8; iter++)
//    {
//        tempPixels[iter] = pixelColor;
//    }
//
//    // update texture with pixel buffer
//    SDL_UpdateTexture(texture, NULL, tempPixels, 8 * sizeof(Uint32));
//
//    delete[] tempPixels;
//    SDL_Rect srcRect;
//    srcRect.x = 0;
//    srcRect.y = 0;
//    srcRect.w = 8;
//    srcRect.h = 8;
//
//    SDL_Rect dstRect;
//    dstRect.x = x;
//    dstRect.y = y;
//    dstRect.w = 8;
//    dstRect.h = 8;
//
//    SDL_RenderCopy(_renderer, texture, &srcRect, &dstRect);
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

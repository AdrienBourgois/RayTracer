#include <iostream>
#include "Driver.h"
#include "Window.h"
#include "Log.h"
#include "Reflexion.h"

Driver::Driver()
{
    Log* log = Log::getInstance();
    log->info("Driver creation...");
    this->window.reset(new Window);
    this->screenSurface = nullptr;
    this->format = nullptr;
    log->info("Driver created.");
}

Driver::~Driver()
{
    Log* log = Log::getInstance();
    log->info("Driver destroying...");
    this->window = nullptr;
    this->screenSurface = nullptr;
    this->format = nullptr;
    SDL_Quit();
    log->info("Driver destroyed.");
}

auto Driver::init(Vector2D<int> screen_res) -> void
{
    Log* log = Log::getInstance();
    log->info("Driver initialization...");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        log->error("Error: in method Driver::init() SDL initialization failed.");
    else
        this->window->init("RayTracing", screen_res);

    this->screenSurface = SDL_GetWindowSurface(this->window->getWindow());
    this->format = this->screenSurface->format;
    this->mapRGB = SDL_MapRGB(this->screenSurface->format, 255, 0, 0);
    SDL_FillRect(this->screenSurface, nullptr, this->mapRGB);

	this->changePixelColor(0, 255, 0, 240, 300);

	this->reflexion = new Reflexion();

	this->reflexion->calculateReflexion();
	this->reflexion->calculateRefraction();

	Uint8 r = 0, g = 0, b = 0;
	this->getPixelColor(240, 300, &r, &g, &b);
	std::cout << "r value :" << (unsigned int)r << std::endl; 
	std::cout << "g value :" << (unsigned int)g << std::endl;
	std::cout << "b value :" << (unsigned int)b << std::endl;
    log->info("Driver initialized.");
}

auto Driver::render() -> void
{
    this->window->update();
}

auto Driver::close() -> void
{
    Log* log = Log::getInstance();
    log->info("Driver closing...");
    this->window->close();
    log->info("Driver closed.");
}

auto Driver::changePixelColor(Uint8 r, Uint8 g, Uint8 b, int pos_x, int pos_y) -> void
{
	Uint32 *_pixels = (Uint32 *)this->screenSurface->pixels;
	
	Uint32 pixel = _pixels[(1 * this->screenSurface->w) + 1];// copy of a screen pixel
	pixel = SDL_MapRGB(this->format, r, g, b);// new pixel color : RGB format

	_pixels[( pos_y * this->screenSurface->w) + pos_x] = pixel;//x = screen length, y = screen width
								   //(y * surface->w) + x
}

auto Driver::getPixelColor(int pos_x, int pos_y, Uint8* r, Uint8* g, Uint8* b) -> void
{
	Uint32 *pixels_list = (Uint32 *)this->screenSurface->pixels;
	
	Uint32 pixel = pixels_list[(pos_y * this->screenSurface->w) + pos_x];
	SDL_GetRGB(pixel, this->format, r, g, b);
}


#include <iostream>
#include "Driver.h"
#include "Window.h"

Driver::Driver()
{
    this->window.reset(new Window);
    this->screenSurface = nullptr;
    this->format = nullptr;
}

Driver::~Driver()
{
    this->window = nullptr;
    this->screenSurface = nullptr;
    this->format = nullptr;
    SDL_Quit();
}

auto Driver::init(Vector2D<int> screen_res) -> void
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cout<<"SDL init failed"<<std::endl;
    else
        this->window->init("RayTracing", screen_res);

    this->screenSurface = SDL_GetWindowSurface(this->window->getWindow());
    this->format = this->screenSurface->format;
    this->mapRGB = SDL_MapRGB(this->screenSurface->format, 255, 0, 0);
    SDL_FillRect(this->screenSurface, nullptr, this->mapRGB);

/*	// ----------- CHANGING 1 PIXEL COLOR -----------------------

	Uint32 *_pixels = (Uint32 *)this->screenSurface->pixels;	

	Uint32 pixel = _pixels[(1 * this->screenSurface->w) + 1]; // copy of a screen pixel
	pixel = SDL_MapRGB(this->format, 0,255,0); // new pixel color : RGB format 
	
	_pixels[( 239 * this->screenSurface->w) + 319] = pixel;	//x = screen length, y = screen width
								//(y * surface->w) + x

	// ----------- CHANGING 1 PIXEL COLOR -----------------------*/
}

auto Driver::render() -> void
{
    this->window->update();
}

auto Driver::close() -> void
{
    this->window->close();
}

auto Driver::changePixelColor(int r, int g, int b, int pos_x, int pos_y) -> void
{
	Uint32 *_pixels = (Uint32 *)this->screenSurface->pixels;
	
	Uint32 pixel = _pixels[(1 * this->screenSurface->w) + 1];
	pixel = SDL_MapRGB(this->format, r, g, b);

	_pixels[( pos_y * this->screenSurface->w) + pos_x] = pixel;
}

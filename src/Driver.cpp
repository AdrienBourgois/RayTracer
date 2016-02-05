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
    this->mapRGB = SDL_MapRGB(this->screenSurface->format, 0, 0, 0);
    SDL_FillRect(this->screenSurface, nullptr, this->mapRGB);
}

auto Driver::render() -> void
{
    this->window->update();
}

auto Driver::close() -> void
{
    this->window->close();
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


#include <iostream>

#include "Driver.h"
#include "Window.h"
#include "Log.h"
#include "RenderBuffer.h"

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

auto Driver::init(Vector2D<float> screen_res) -> void
{
    Log* log = Log::getInstance();
    log->info("Driver initialization...");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        log->error("Error: in method Driver::init() SDL initialization failed.");
    else
        this->window->init("RayTracing", screen_res);

    this->screenSurface = SDL_GetWindowSurface(this->window->getWindow());
    this->format = this->screenSurface->format;
    this->mapRGB = SDL_MapRGB(this->screenSurface->format, 145, 114, 114);
    SDL_FillRect(this->screenSurface, nullptr, this->mapRGB);

    log->info("Driver initialized.");
}

auto Driver::render() -> void
{
    this->window->update();
	this->mapRGB = SDL_MapRGB(this->screenSurface->format, 0, 0, 0);
	SDL_FillRect(this->screenSurface, nullptr, this->mapRGB);
}

auto Driver::close() -> void
{
    Log* log = Log::getInstance();
    log->info("Driver closing...");
    this->window->close();
    log->info("Driver closed.");
}

auto Driver::changePixelColor(std::vector<Vector3D<Uint8>>* color_list, std::vector<Vector2D<float>>* screen_coord_list) -> void
{
    //unsigned int idx = 0;
    //while(idx<screen_coord_list.size())
    for(unsigned int idx = 0; idx < screen_coord_list->size(); ++idx)
    {
        //for(unsigned int idx2 = 0; idx2 < color_list.size(); ++idx)
        //{
            Vector2D<float> actual_screen_coord = screen_coord_list->at(idx);
            //Vector2D<float> actual_screen_coord = (*screen_coord_list)[idx];
            Vector3D<Uint8> actual_color = color_list->at(idx);

	        Uint32 *_pixels = (Uint32 *)this->screenSurface->pixels;
	
	        Uint32 pixel = _pixels[(0 * this->screenSurface->w) + 0];// copy of a screen pixel
	        pixel = SDL_MapRGB(this->format, actual_color.x, actual_color.y, actual_color.z);// new pixel color : RGB format

	        _pixels[(int (actual_screen_coord.y) * this->screenSurface->w) + int (actual_screen_coord.x)] = pixel;//x = screen length, y = screen width
        //}						   
        //++idx;
    }
}

auto Driver::getPixelColor(int pos_x, int pos_y, Uint8* r, Uint8* g, Uint8* b) -> void
{
	Uint32 *pixels_list = (Uint32 *)this->screenSurface->pixels;
	
	Uint32 pixel = pixels_list[(pos_y * this->screenSurface->w) + pos_x];
	SDL_GetRGB(pixel, this->format, r, g, b);
}


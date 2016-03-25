#include <iostream>
#include "Driver.h"
#include "Window.h"
#include "SceneNode.h"
#include "Log.h"

Driver::Driver()
{
    Log* log = Log::getInstance();
    log->info("Driver creation...");
    this->window.reset(new Window);
    this->screenSurface = nullptr;
    this->format = nullptr;
    this->raytracer = nullptr;
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

auto Driver::init(Vector2D<float> screen_res, Raytracer* raytr) -> void
{
    Log* log = Log::getInstance();
    log->info("Driver initialization...");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        log->error("Error: in method Driver::init() SDL initialization failed.");
    else
        this->window->init("RayTracing", screen_res);
    this->raytracer = raytr;

    this->screenSurface = SDL_GetWindowSurface(this->window->getWindow());
    this->format = this->screenSurface->format;
    this->mapRGB = SDL_MapRGB(this->screenSurface->format, 0, 0, 0); 
    SDL_FillRect(this->screenSurface, nullptr, this->mapRGB);

    log->info("Driver initialized.");
}

auto Driver::render() -> void
{
    this->changePixelColor(this->raytracer->getRenderBuffer()->getColorList(), this->raytracer->getRenderBuffer()->getScreenCoordList());
    this->raytracer->getRenderBuffer()->clearBuffer();
    this->window->update();
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
    for(unsigned int idx = 0; idx < screen_coord_list->size(); ++idx)
    {
            Vector2D<float> actual_screen_coord = screen_coord_list->at(idx);
            Vector3D<Uint8> actual_color = color_list->at(idx);

            Uint32 *_pixels = (Uint32 *)this->screenSurface->pixels;

            Uint32 pixel = _pixels[(0 * this->screenSurface->w) + 0];// copy of a screen pixel
            pixel = SDL_MapRGB(this->format, actual_color.x, actual_color.y, actual_color.z);// new pixel color : RGB format

            _pixels[(int (actual_screen_coord.y) * this->screenSurface->w) + int (actual_screen_coord.x)] = pixel;//x = screen length, y = screen width
    }
}


auto Driver::getPixelColor(int pos_x, int pos_y, Uint8* r, Uint8* g, Uint8* b) -> void
{
    Uint32 *pixels_list = (Uint32 *)this->screenSurface->pixels;
    
    Uint32 pixel = pixels_list[(pos_y * this->screenSurface->w) + pos_x];
    SDL_GetRGB(pixel, this->format, r, g, b); 
}


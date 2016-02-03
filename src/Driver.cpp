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
}

auto Driver::render() -> void
{
    this->window->update();
}

auto Driver::close() -> void
{
    this->window->close();
}


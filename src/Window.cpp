#include "Window.h"

Window::Window()
{
    this->window = nullptr;
    //this->screenSurface = nullptr;
    //this->format = nullptr;
}

auto Window::init(const char* title, Vector2D<int> screen_res) -> void
{
    this->screen_size = screen_res;
    this-> window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_size.x, screen_size.y, SDL_WINDOW_SHOWN);

    SDL_assert(window);
}

auto Window::update() -> void
{
    SDL_UpdateWindowSurface(this->window);
}

auto Window::close() -> void
{
    SDL_DestroyWindow(this->window);
}

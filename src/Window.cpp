#include "Window.h"
#include "Log.h"

Window::Window()
{
    Log* log = Log::getInstance();
    log->info("Window creation...");
    this->window = nullptr;
    //this->screenSurface = nullptr;
    //this->format = nullptr;
    log->info("Window created.");
}

auto Window::init(const char* title, Vector2D<int> screen_res) -> void
{
    Log* log = Log::getInstance();
    log->info("Window initialization...");
    this->screen_size = screen_res;
    this-> window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_size.x, screen_size.y, SDL_WINDOW_SHOWN);

    SDL_assert(window);
    log->info("Window initialized.");
}

auto Window::update() -> void
{
    SDL_UpdateWindowSurface(this->window);
}

auto Window::close() -> void
{
    Log* log = Log::getInstance();
    SDL_DestroyWindow(this->window);
    log->info("Window closed.");
}

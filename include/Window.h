#ifndef __WINDOW_DECLARATION__
#define __WINDOW_DECLARATION__

#include <SDL2/SDL.h>

#include "Vector.h"

class Window final
{
    public:
        Window();
        Window(Window const&) = delete;
        ~Window();

        auto init(const char* title, Vector2D<float> screen_res) -> void;
        auto update() -> void;
        auto close() -> void;

        auto  getWindow() const -> SDL_Window*  { return this->window; }
        auto  getScreenSize() const -> Vector2D<int> { return this->screen_size; }

    private:
        SDL_Window* window;
        Vector2D<int> screen_size;
};
#endif


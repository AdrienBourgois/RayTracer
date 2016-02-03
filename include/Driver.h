#ifndef __DRIVER_DECLARATION__
#define __DRIVER_DECLARATION__

#include <SDL2/SDL.h>
#include <memory>

#include "Vector.h"

class Window;

class Driver final
{
    public:
        Driver();
        Driver(Driver const&) = delete;
        ~Driver();

        auto operator =(Driver const&) -> Driver& = delete;
        auto init( Vector2D<int> screen_res) -> void;
        auto render() -> void;
        auto close() -> void;
    private:
        std::unique_ptr<Window>     window;
        SDL_Surface* screenSurface;
        SDL_PixelFormat* format;
        Uint32 mapRGB;
};

#endif

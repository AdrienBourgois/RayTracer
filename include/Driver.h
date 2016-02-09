#ifndef __DRIVER_DECLARATION__
#define __DRIVER_DECLARATION__

#include <SDL2/SDL.h>
#include <memory>

#include "Vector.h"

class Window;

class Reflexion;

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

	auto changePixelColor(Uint8 r, Uint8 g, Uint8 b, int pos_x, int pos_y) -> void;
	auto getPixelColor(int pos_x, int pos_y, Uint8* r, Uint8* g, Uint8* b) -> void;
 
    private:
        std::unique_ptr<Window>     window;
		Reflexion*					reflexion;
        SDL_Surface* screenSurface;
        SDL_PixelFormat* format;
        Uint32 mapRGB;
};

#endif

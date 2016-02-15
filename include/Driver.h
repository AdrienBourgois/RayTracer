#ifndef __DRIVER_DECLARATION__
#define __DRIVER_DECLARATION__

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "Vector.h"

class Window;

class Driver final
{
    public:
        Driver();
        Driver(Driver const&) = delete;
        ~Driver();

        auto operator =(Driver const&) -> Driver& = delete;
        auto init( Vector2D<float> screen_res) -> void;
        auto render() -> void;
        auto close() -> void;

	auto changePixelColor(std::vector<Vector3D<Uint8>> color_list, std::vector<Vector2D<float>>) -> void;
	auto getPixelColor(int pos_x, int pos_y, Uint8* r, Uint8* g, Uint8* b) -> void;
 
    private:
        std::unique_ptr<Window>     window;
        SDL_Surface* screenSurface;
        SDL_PixelFormat* format;
        Uint32 mapRGB;
};

#endif

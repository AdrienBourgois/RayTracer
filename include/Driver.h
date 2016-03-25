#ifndef __DRIVER_DECLARATION__
#define __DRIVER_DECLARATION__

#include <SDL2/SDL.h>
#include <memory>

#include "Vector.h"
#include "Raytracer.h"

class Window;

class Driver final
{
    public:
        Driver();
        Driver(Driver const&) = delete;
        Driver(Driver&&) = delete;
        ~Driver();

        auto operator =(Driver const&) -> Driver& = delete;
        auto operator =(Driver&&) -> Driver& = delete;

        auto init( Vector2D<float> screen_res, Raytracer* raytr) -> void;
        auto render() -> void;
        auto close() -> void;

	auto changePixelColor(std::vector<Vector3D<Uint8>>* color_list, std::vector<Vector2D<float>>* screen_coord_list) -> void;
	auto getPixelColor(int pos_x, int pos_y, Uint8* r, Uint8* g, Uint8* b) -> void;

    private:
        std::unique_ptr<Window>	window;
        SDL_Surface*		screenSurface;
        SDL_PixelFormat*	format;
        Uint32			mapRGB;
	Raytracer*		raytracer;
};

#endif


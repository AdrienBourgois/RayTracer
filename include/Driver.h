#ifndef __DRIVER_DECLARATION__
#define __DRIVER_DECLARATION__

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "Vector.h"

class RenderBuffer;
class Camera;
class Ray;
class SceneNode;

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

        auto convert(Vector2D<int> vec) -> Vector2D<float>;

	auto changePixelColor(Uint8 r, Uint8 g, Uint8 b, std::vector<Vector2D<float>>) -> void;
	auto getPixelColor(int pos_x, int pos_y, Uint8* r, Uint8* g, Uint8* b) -> void;
 
    private:
        std::unique_ptr<Window>     window;
        SDL_Surface* screenSurface;
        SDL_PixelFormat* format;
        Uint32 mapRGB;
        
        std::unique_ptr<RenderBuffer> render_buffer;
        std::unique_ptr<Camera>     camera;
        Vector2D<int>               screen_size;
        Vector2D<float>             f_screen_size;
        Ray*                        ray;
        SceneNode*                  node_test;        
        bool                        collision_result;
};

#endif

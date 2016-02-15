#ifndef __RENDERBUFFER_DECLARATION__
#define __RENDERBUFFER_DECLARATION__

#include <vector>
#include <SDL2/SDL.h>

#include "Vector.h"

class RenderBuffer
{
    public:
        RenderBuffer();
        RenderBuffer(RenderBuffer const&) = delete;
        ~RenderBuffer() = default;

        auto setColorList(Vector3D<Uint8> col) -> void; 
        auto setScreenCoordList(Vector2D<float> screen_coord) -> void; 

        auto getColorList() -> std::vector<Vector3D<Uint8>>; 
        auto getScreenCoordList() -> std::vector<Vector2D<float>>; 

    private:

        std::vector<Vector3D<Uint8>> color_list;
        std::vector<Vector2D<float>> screen_coord_list;
};

#endif

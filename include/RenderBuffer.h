#ifndef __RENDERBUFFER_DECLARATION__
#define __RENDERBUFFER_DECLARATION__

#include "Vector.h"
#include <vector>

class RenderBuffer
{
    public:
        RenderBuffer();
        RenderBuffer(RenderBuffer const&) = delete;
        ~RenderBuffer() = default;

        auto setColorList(Vector3D<float> col) -> void; 
        auto setScreenCoordList(Vector2D<float> screen_coord) -> void; 

        auto getColorList() -> std::vector<Vector3D<float>>; 
        auto getScreenCoordList() -> std::vector<Vector2D<float>>; 

    private:

        std::vector<Vector3D<float>> color_list;
        std::vector<Vector2D<float>> screen_coord_list;
};

#endif

#ifndef __RENDERBUFFER_DECLARATION__
#define __RENDERBUFFER_DECLARATION__

#include "Vector.h"
#include <vector>

class RenderBuffer
{
    public:
        RenderBuffer() = default;
        ~RenderBuffer() = default;

        auto setColorList(Vector3D<float> col) -> void { this->color_list.push_back(col); }
        auto setScreenCoordList(Vector2D<float> screen_coord) -> void { this->screen_coord_list.push_back(screen_coord); }

        auto getColorList() -> std::vector<Vector3D<float>> { return this->color_list; }
        auto getScreenCoordList() -> std::vector<Vector2D<float>> { return this->screen_coord_list; }

    private:

        std::vector<Vector3D<float>> color_list;
        std::vector<Vector2D<float>> screen_coord_list;
};

#endif

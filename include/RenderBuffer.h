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
		auto setColorAtIndex(Vector3D<Uint8> col, long unsigned int idx) -> void;
        auto setScreenCoordList(Vector2D<float> screen_coord) -> void; 

        auto getColorList() -> std::vector<Vector3D<Uint8>>*; 
        auto getScreenCoordList() -> std::vector<Vector2D<float>>*; 
		auto getLastColorElementIndex() -> long unsigned int;

        auto clearBuffer() -> void;

        template<typename T>
        auto getFormattedData(bool alpha);

    private:

        std::vector<Vector3D<Uint8>> color_list;
        std::vector<Vector2D<float>> screen_coord_list;
};

#endif

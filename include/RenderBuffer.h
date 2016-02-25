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
        auto getFormattedData(bool alpha) -> T*;

    private:

        std::vector<Vector3D<Uint8>> color_list;
        std::vector<Vector2D<float>> screen_coord_list;
};

template <typename T>
auto RenderBuffer::getFormattedData(bool alpha) -> T*
{
    int pixelSize = this->screen_coord_list.size();
    T* formattedData = new T[pixelSize * (3 + alpha)];

    for (int i = 0; i < pixelSize; ++i)
    {
        formattedData[i] = this->color_list[i].x;
        formattedData[i+1] = this->color_list[i].y;
        formattedData[i+2] = this->color_list[i].z;
        //if(alpha)
        //    formattedData[i+3] = this->color_list[i].alpha;
    }

    return formattedData;
}

#endif

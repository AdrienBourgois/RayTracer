#ifndef __RENDERBUFFER_DECLARATION__
#define __RENDERBUFFER_DECLARATION__

#include <vector>
#include <cstdint>

#include "Vector.h"

typedef unsigned char uint8;

class RenderBuffer
{
    public:
        RenderBuffer();
        RenderBuffer(RenderBuffer const&) = delete;
        RenderBuffer(RenderBuffer&&) = delete;
        ~RenderBuffer() = default;

	auto operator =(RenderBuffer const&) -> RenderBuffer& = delete;
	auto operator =(RenderBuffer&&) -> RenderBuffer& = delete;

        auto setColorList(Vector3D<float> col) -> void; 
	auto setColorAtIndex(Vector3D<uint8> col, long unsigned int idx) -> void;
        auto setScreenCoordList(Vector2D<float> screen_coord) -> void; 

        auto getColorList() -> std::vector<Vector3D<uint8>>*; 
        auto getScreenCoordList() -> std::vector<Vector2D<float>>*; 
	auto getLastColorElementIndex() -> long unsigned int;
		
	auto correctColor(Vector3D<float> color) -> Vector3D<float>;

        auto clearBuffer() -> void;

        template<typename T>
        auto getFormattedData(bool alpha) -> T*;

    private:

        std::vector<Vector3D<uint8>> color_list;
        std::vector<Vector2D<float>> screen_coord_list;
};

template <typename T>
auto RenderBuffer::getFormattedData(bool alpha) -> T*
{
    int pixelSize = this->screen_coord_list.size();
    T* formattedData = new T[pixelSize * (3 + alpha)];

    for (int i = 0; i < pixelSize; ++i)
    {
        formattedData[(i)*3] = this->color_list[i].x;
        formattedData[(i+1)*3] = this->color_list[i].y;
        formattedData[(i+2)*3] = this->color_list[i].z;
    }

    return formattedData;
}

#endif

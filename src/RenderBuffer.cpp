#include "RenderBuffer.h"
#include "Log.h"

RenderBuffer::RenderBuffer()
{
    Log* log = Log::getInstance();
    log->info("RenderBuffer created.");
}

auto RenderBuffer::setColorList(Vector3D<float> col) -> void
{
	Vector3D<uint8> color;

	color = color.cast(this->correctColor(col));

    this->color_list.push_back(color);
}

auto RenderBuffer::setColorAtIndex(Vector3D<uint8> col, long unsigned int idx) -> void
{
	this->color_list[idx] = col;
}

auto RenderBuffer::setScreenCoordList(Vector2D<float> screen_coord) -> void
{
    this->screen_coord_list.push_back(screen_coord);
}

auto RenderBuffer::getColorList() -> std::vector<Vector3D<uint8>>*
{
    return &this->color_list;
}

auto RenderBuffer::getScreenCoordList() -> std::vector<Vector2D<float>>*
{
    return &this->screen_coord_list;
}

auto RenderBuffer::getLastColorElementIndex() -> long unsigned int
{
	return this->color_list.size() - 1;
}

auto RenderBuffer::correctColor(Vector3D<float> color) -> Vector3D<float>
{
	if (color.x > 255.f)
		color.x = 255.f;
	if (color.y > 255.f)
        color.y = 255.f;
	if (color.z > 255.f)
        color.z = 255.f;	

	return color;
}

auto RenderBuffer::clearBuffer() -> void
{
    this->color_list.clear();
    this->screen_coord_list.clear();
}

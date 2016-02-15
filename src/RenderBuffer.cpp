#include "RenderBuffer.h"
#include "Log.h"

RenderBuffer::RenderBuffer()
{
    Log* log = Log::getInstance();
    log->info("RenderBuffer created.");
}

auto RenderBuffer::setColorList(Vector3D<Uint8> col) -> void
{
    this->color_list.push_back(col);
}

auto RenderBuffer::setScreenCoordList(Vector2D<float> screen_coord) -> void
{
    this->screen_coord_list.push_back(screen_coord);
}

auto RenderBuffer::getColorList() -> std::vector<Vector3D<Uint8>>
{
    return this->color_list;
}

auto RenderBuffer::getScreenCoordList() -> std::vector<Vector2D<float>>
{
    return this->screen_coord_list;
}

#include "Ray.h"
#include "RenderBuffer.h"
Ray::Ray(Vector3D<float> position, Vector2D<float> screen_size, float idx_x, float idx_y, RenderBuffer* rend_buff)
{
    this->render_buffer = rend_buff;
    this->start_point = position;
    
    this->findDestPoint(screen_size, idx_x, idx_y);

    this->direction = this->dest_point - start_point;

    //this->run();
}

auto Ray::findDestPoint(Vector2D<float> screen_size, float idx_x, float idx_y) -> void
{

    float NDC_x = (idx_x +0.5f) / screen_size.x;
    float NDC_y = (idx_y +0.5f) / screen_size.y;

    this->dest_point.x = ((2.f * NDC_x) - 1.f) * (screen_size.x / screen_size.y);
    this->dest_point.y = 1.f - (2.f * NDC_y);
    
}

auto Ray::run(Vector2D<float> screen_size, float idx_x, float idx_y) -> void
{
(void) screen_size;
    (void) idx_x;
    (void)idx_y;
}

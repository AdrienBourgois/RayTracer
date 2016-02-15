#include <math.h>

#include "Ray.h"
#include "RenderBuffer.h"
#include "SceneNode.h"
#include "Driver.h"
#include "Log.h"
#include "Collision.h"


Ray::Ray(Vector3D<float> position, Vector2D<float> screen_res, RenderBuffer* rend_buff, SceneNode* node, Driver* drv)
{
    Log* log = Log::getInstance();
    log->info("Ray creation...");

    this->screen_size = screen_res;
    this->driver = drv;
    this->scene_node = node;
    this->lenght_max = 1000.f;
    this->render_buffer = rend_buff;
    this->start_point = position;
    this->collision_result = false;

    log->info("Ray created.");
}

auto Ray::findDestPoint(float idx_x, float idx_y) -> void
{
    float NDC_x = (idx_x +0.5f) / this->screen_size.x;
    float NDC_y = (idx_y +0.5f) / this->screen_size.y;

    this->dest_point.x = ((2.f * NDC_x) - 1.f) * (this->screen_size.x / this->screen_size.y);
    this->dest_point.y = 1.f - (2.f * NDC_y);

    this->findDirection();
}

auto Ray::findDirection() -> void
{
    this->direction = this->dest_point - this->start_point;
}

auto Ray::run() -> void
{
    for (float idx_y = 0.f; idx_y < this->screen_size.y; ++idx_y)
    {
        for (float idx_x = 0.f; idx_x < this->screen_size.x; ++idx_x)
        {
            this->findDestPoint(idx_x, idx_y);
            Collision collision = Collision(); 
           if(collision.detectCollision(this, this->scene_node))
            {
                this->render_buffer->setColorList(Vector3D<float>(255.f, 0.f, 0.f));
                this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
            }
        }
    }
}

auto Ray::close() -> void
{
    this->render_buffer = nullptr;
    this->scene_node = nullptr;
    this->driver = nullptr;
    this->collision_result = false;
}

auto Ray::DOT(Vector3D<float> vector_1, Vector3D<float> vector_2) -> float
{
    float result = vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z;
    return result;
}

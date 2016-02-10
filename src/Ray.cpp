#include <math.h>

#include "Ray.h"
#include "RenderBuffer.h"
#include "SceneNode.h"
#include "Driver.h"
Ray::Ray(Vector3D<float> position, Vector2D<float> screen_size, float idx_x, float idx_y, RenderBuffer* rend_buff, SceneNode* node, Driver* drv)
{
    this->driver = drv;
    this->scene_node = node;
    this->lenght_max = 1000.f;
    this->render_buffer = rend_buff;
    this->start_point = position;
    
    this->findDestPoint(screen_size, idx_x, idx_y);

    this->direction = this->dest_point - start_point;

}

auto Ray::findDestPoint(Vector2D<float> screen_size, float idx_x, float idx_y) -> void
{

    float NDC_x = (idx_x +0.5f) / screen_size.x;
    float NDC_y = (idx_y +0.5f) / screen_size.y;

    this->dest_point.x = ((2.f * NDC_x) - 1.f) * (screen_size.x / screen_size.y);
    this->dest_point.y = 1.f - (2.f * NDC_y);

    this->findDirection();
}

auto Ray::findDirection() -> void
{
    this->direction = this->dest_point - this->start_point;
}

auto Ray::run(Vector2D<float> screen_size, float idx_x, float idx_y) -> void
{
    bool collision_result = false;
    Ray* ray = nullptr;
    (void)ray;

    this->findDestPoint(screen_size, idx_x, idx_y);
    this->direction = this->dest_point - start_point;
    collision_result = this->collision();

    if(collision_result)
        this->driver->changePixelColor(255, 0, 0, int(idx_y), int(idx_x));

        if(idx_y <= screen_size.y)
        {
            if(idx_x < screen_size.x)
                ++idx_x;
            else if(idx_x == screen_size.x)
            {
                idx_x = 0.f;
                ++idx_y;
            }
            std::cout<<"idx_x = "<<idx_x<<"   "<<"idx_y = "<<idx_y<<std::endl;
            ray = new Ray(this->start_point, screen_size, idx_x, idx_y, this->render_buffer, this->scene_node, this->driver);
        }       
}

auto Ray::collision() -> bool
{
    //Vector3D<float> ray_dir = ray.getRayDirection();
    //Vector3D<float> ray_origin = ray.getRayOrigin();
    Vector3D<float> circle_posi = scene_node->getPosition();

    //float ray_length = ray.getRayMaxLenght();
    float circle_radius = scene_node->getRadius(); // get rad

    float A = this->DOT(this->direction, this->direction);
    Vector3D<float> dist = this->start_point - circle_posi;

    float B = 2 * DOT(this->direction, dist);

    float C = DOT(dist, dist) - (circle_radius * circle_radius);

    float discri = B * B - 4 * A * C;
    if (discri < 0)
        return false; // no colision
    else
    {   
        float sqrt_discri = (float)(sqrt(discri));
        float t0 = (-B + sqrt_discri)/(2);
        float t1 = (-B - sqrt_discri)/(2);
                                                            
        // We want the closest one 
        if (t0 > t1) 
        t0 = t1; 

       // Verify t0 larger than 0 and less than the original t 
        if ((t0 > 0.001f) && (t0 < this->lenght_max))
            return true;
    }
    return false;
// see how to get model color for the ray
}

auto Ray::DOT(Vector3D<float> vector_1, Vector3D<float> vector_2) -> float
{
    float result = vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z;
    return result;
}

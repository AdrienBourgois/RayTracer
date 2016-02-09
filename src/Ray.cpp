#include "Ray.h"
#include "RenderBuffer.h"
Ray::Ray(Vector3D<float> position, Vector2D<float> screen_size, float idx_x, float idx_y, RenderBuffer* rend_buff, SceneNode* node)
{
    this->scene_node = node;
    this->lenght_max = 1000.f;
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

auto Ray::collision() -> void
{
    /*Vector3D<float> ray_dir = ray.getRayDirection();
    Vector3D<float> ray_origin = ray.getRayOrigin();
    Vector3D<float> circle_posi = circle.getPosition();
    float ray_length = ray.getRayMaxLenght();
    float circle_radius = circle.getRadius(); // get rad

    float A = DOT(ray_dir, ray_dir);
    Vector3D<float> dist = ray_origin - circle_posi;

    float B = 2 * DOT(ray_dir, dist);

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
        if ((t0 > 0.001f) && (t0 < ray_length))
            return true;
    }
    return false;
// see how to get model color for the ray*/
}

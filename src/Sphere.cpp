#include "Sphere.h"

Sphere::Sphere(Vector3D<float> position_, float radius_)
: radius(radius_), position(position_)
{}

/* auto Sphere::ray_collide(Vector3D<float> point, Vector3D<float> direction) -> bool
{
    
} */

auto project(Vector3D<float> u, Vector3D<float> v) -> Vector3D<float>
{
    return ((v * u) / v.norm()) * v;
}

/* auto distance_to_ray(Vector3D<float> point, Vector3D<float> direction) -> float
{

} */

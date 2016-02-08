#ifndef __SPHERE_DECLARATION__
#define __SPHERE_DECLARATION__

#include "Vector.h"

class Sphere
{
    public:
        Sphere() = default;
        ~Sphere() = default;

        Sphere(Sphere const&) = delete;
        Sphere(Sphere &&) = delete;
        auto operator=(Sphere const&) -> Sphere = delete;
        auto operator=(Sphere &&) -> Sphere = delete;

        auto ray_collide(Vector3D, Vector3D) -> bool;

    private:
        float radius;
        Vector3D<float> position;
};

#endif //__SPHERE_DECLARATION__

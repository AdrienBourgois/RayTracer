#include <cmath>
#include <iostream>

#include "CollisionCalc.h"
#include "Vector.h"
#include "Log.h"

auto calculateCollision(SphereGeometryBuffer* current_geometry, Ray* ray) -> float
{
	Log* log = Log::getInstance();
	
	if(current_geometry == nullptr)
		log->error("Can't calculate collision. Reason: current_geometry is null.");

	Vector3D<float> circle_posi = current_geometry->position;
	float circle_radius = current_geometry->radius;

	float A = ray->direction.dot(ray->direction);
	Vector3D<float> dist = ray->origin - circle_posi;

	float B = 2 * ray->direction.dot(dist);

	float C = dist.dot(dist) - (circle_radius * circle_radius);

	float discri = B * B - 4 * A * C;

	if (discri < 0)
	{
		return -1.f; // no colision
	}
	else
	{
		//std::cout<<"Collision inside else"<<std::endl;
		float sqrt_discri = (float)(sqrt(discri));
        float t0 = (-B + sqrt_discri)/(2);
        float t1 = (-B - sqrt_discri)/(2);

        // We want the closest one 
        if (t0 > t1)
		{
            t0 = t1;
		}


       // Verify t0 larger than 0 and less than the original t 
        if ((t0 > 0.001f) && (t0 < ray->lenght))
        {
            return t0;
        }
    }
    return -1.f;	
}

auto calculateCollisionPoint(float distance, Ray* ray) -> void
{
	ray->collision_point = (ray->direction * distance) + ray->origin;
}

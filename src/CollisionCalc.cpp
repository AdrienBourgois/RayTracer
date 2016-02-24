#include <cmath>

#include "CollisionCalc.h"
#include "Vector.h"
#include "Log.h"

auto calculateCollision(GeometryBuffer* current_geometry, Ray* ray) -> bool
{
	Log* log = Log::getInstance();
	
	if(current_geometry == nullptr)
		log->error("Can't calculate collision. Reason: current_geometry is null.");

	Vector3D<float> circle_posi = current_geometry->position;
	float circle_radius = (SphereGeometryBuffer)current_geometry->radius;

	float A = ray->direction.dot(ray->direction);
	Vector3D<float> dist = ray->origin - current_geometry->position;

	float B = 2 * ray->direction.dot(dist);

	float C = dist.dot(dist) - (current_geometry->radius * current_geometry->radius);

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
        {
            this->calculateCollisionPoint(t0);
            return true;
        }
    }
    return false;	
}

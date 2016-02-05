#include <math.h>

#include "Collision.h"
#include "Ray.h"
#include "SceneNode.h"

namespace
{
	auto DOT(Vector3D<float> vector_1, Vector3D<float> vector_2) -> float
	{
		float result = vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z;
		return result;
	}
} // namespace end
/*
auto Shpere::raySphereIntersection(Ray ray, float &t1, float &t2)
{
	Vector3D<float> dist = sphere_center - ray.getStartPosi();
	float tca = dist.dot(ray.getRayDir());
	
	if (tca < 0)
		return false; // no collision

	float d2 = dist.dot(dist) - tca * tca;
	if (d2 > radius2) // radius2 = sphere radius^2
		return false; // no collision

	float thc = sqrt(radius2 - d2); // square root of radius2 - d2
	t1 = tca - thc; // check if t1 < 0 if t1 = t2
	t2 = tca + thc;

	return true;
}
*/
auto Collision::rayCircleCollision(Ray ray, SceneNode circle) -> bool
{
	Vector3D<float> ray_dir = ray.getRayDirection();
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
// see how to get model color for the ray

	}
	return false;
}

auto Collision::rayPlaneCollision(Ray ray, SceneNode plane) -> bool
{
	Vector3D<float> pos = plane.getPosition();
	Vector3D<float> ray_dir = ray.getRayDirection();

	float intersec = DOT(pos, ray_dir);

	if (intersec < 0 || intersec > 0)
		return true;

	return false;
}

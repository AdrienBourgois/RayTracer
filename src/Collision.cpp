#include <math.h>
#include <vector>

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
	Vector3D<float> ray_dir = ray.getRayDirection();
	Vector3D<float> ray_origin = ray.getRayOrigin();

	Vector3D<float> a_point = plane.getRectAPoint();
	Vector3D<float> b_point = plane.getRectBPoint();
	Vector3D<float> c_point = plane.getRectCPoint();

	float ray_length = ray.getRayMaxLenght();

//	std::cout << "a : " << a_point << std::endl;
//	std::cout << "b : " << b_point << std::endl;
//	std::cout << "c : " << c_point << std::endl;

	Vector3D<float> ab = b_point - a_point;
	Vector3D<float> ac = c_point - a_point;

//	std::cout << "ab : " << ab << std::endl;
//	std::cout << "ac : " << ac << std::endl;

	Vector3D<float> n = ab * ac;
	float d = -(n.x * a_point.x + n.y * a_point.y + n.z * a_point.z);
//	std::cout << "d : " << d << std::endl;

	if (DOT(ray_dir, n) < -001.f && DOT(ray_dir, n) > 0.001f)
		return false;
	
	float t = -(DOT(ray_origin, n) + d) / (DOT(ray_dir, n));
//	std::cout << "t : " << t << std::endl;

	if ((t > 0.001f) && (t < ray_length))
		return true;

	return false;
}


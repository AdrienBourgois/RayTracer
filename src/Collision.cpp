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

//	std::cout << "a : " << a_point << std::endl;
//	std::cout << "b : " << b_point << std::endl;
//	std::cout << "c : " << c_point << std::endl;

	Vector3D<float> ab = b_point - a_point;
	Vector3D<float> ac = c_point - a_point;

//	std::cout << "ab : " << ab << std::endl;
//	std::cout << "ac : " << ac << std::endl;

	Vector3D<float> n = ab * ac;
//	std::cout << "n : " << n << std::endl;

	float d = -(DOT(n, plane.getRectAPoint()));
//	std::cout << "d : " << d << std::endl;

	std::cout << "DOT(ray_dir, n) : " << DOT(ray_dir, n) << std::endl;
	std::cout << "-DOT(ray_origin, n) : " << -(DOT(ray_origin, n)) << std::endl;
	if (DOT(ray_dir, n) < -0001.f && DOT(ray_dir, n) > 0.0001f)
		return false;

	float t = -(DOT(ray_origin, n) + d) / (DOT(ray_dir, n));
	std::cout << "t : " << t << std::endl;
	if (t > 0.f)
		return true;
	

	return false;
}

/*
auto Collision::rayTriangleCollision(Ray ray, SceneNode triangle) -> bool
{
	bool ab_check = checkTriangleABSide(ray, triangle);
	bool ac_check = checkTriangleACSide(ray, triangle);

	if (ab_check == true && ac_check == true)
		return true;

	return false;
}

auto Collision::checkTriangleABSide(Ray ray, SceneNode triangle) -> bool
{
	std::vector<float> _vertice = triangle.getVertice();
	Vector3D<float> ray_origin = ray.getRayOrigin();
	Vector3D<float> ray_dir = ray.getRayDirection() * Vector3D<float>(0.f, 0.f, -ray.getRayMaxLenght());

	Vector3D<float> point_a = Vector3D<float>(_vertice[0], _vertice[1], _vertice[2]) + triangle.getPosition();
	Vector3D<float> point_b = Vector3D<float>(_vertice[3], _vertice[4], _vertice[5]) + triangle.getPosition();

	Vector3D<float> p = ray_origin * ray_dir;

		Vector3D<float> n = (point_a - p) * (point_b - p);
	std::cout << "p : " << p << std::endl;
	std::cout << "(point_a - p) : " << (point_a - p) << std::endl;
	std::cout << "(point_b - p) : " << (point_b - p) << std::endl;
	std::cout << "n : " << n << std::endl;
		Vector3D<float> v = ray_origin - point_a;
		Vector3D<float> w = ray_origin - point_b;

		Vector3D<float> norm = Vector3D<float>((v.y*w.z)-(v.z*w.y), (v.z*w.x)-(v.x*w.z), (v.x*w.y)-(v.y*w.x));
		float d = -DOT(ray_origin, norm);

		if((DOT(p, norm) + d) < 0)
			return false;	
		return true;
}

auto Collision::checkTriangleACSide(Ray ray, SceneNode triangle) -> bool
{
	std::vector<float> _vertice = triangle.getVertice();
	Vector3D<float> ray_origin = ray.getRayOrigin();
	Vector3D<float> ray_dir = ray.getRayDirection() * Vector3D<float>(0.f, 0.f, -ray.getRayMaxLenght());

	Vector3D<float> point_a = Vector3D<float>(_vertice[0], _vertice[1], _vertice[2]) + triangle.getPosition();
	Vector3D<float> point_c = Vector3D<float>(_vertice[6], _vertice[7], _vertice[8]) + triangle.getPosition();

	Vector3D<float> p = ray_origin * ray_dir;

		Vector3D<float> n = (point_a - p) * (point_c - p);

		Vector3D<float> v = ray_origin - point_a;
		Vector3D<float> w = ray_origin - point_c;

		Vector3D<float> norm = Vector3D<float>((v.y*w.z)-(v.z*w.y), (v.z*w.x)-(v.x*w.z), (v.x*w.y)-(v.y*w.x));
		float d = -DOT(ray_origin, norm);

		if((DOT(p, norm) + d) < 0)
			return false;	
		return true;
}*/

auto Collision::rayTriangleCollision(Ray ray, SceneNode triangle) -> bool
{
	std::vector<float> _vertice = triangle.getVertice();

	Vector3D<float> ray_origin = ray.getRayOrigin();
	Vector3D<float> ray_dir = ray_origin + ray.getRayDirection();

	Vector3D<float> a = Vector3D<float>(_vertice[0], _vertice[1], _vertice[2]) + triangle.getPosition();
	Vector3D<float> b = Vector3D<float>(_vertice[3], _vertice[4], _vertice[5]) + triangle.getPosition();
	Vector3D<float> c = Vector3D<float>(_vertice[6], _vertice[7], _vertice[8]) + triangle.getPosition();

	Vector3D<float> ab_edge = b - a;
	Vector3D<float> ac_edge = c - a;

	Vector3D<float> p = ac_edge * ray_dir;
	float deter = DOT(ab_edge, p);
	if (deter == 0)
		return false;

	Vector3D<float> T = ray_origin - a;

	float u = DOT(T, p) * (1.f/deter);
	if (u < 0.f || u > 1.f)
		return false;

	Vector3D<float> q = T * ab_edge;
	
	float v = DOT(ray_dir, q) * (1.f/deter);

	if (v < 0.f || (u + v) > 1.f)
		return false;

	return true;
}

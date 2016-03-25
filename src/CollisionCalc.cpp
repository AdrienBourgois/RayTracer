#include <cmath>
#include <iostream>

#include "CollisionCalc.h"
#include "Vector.h"
#include "Log.h"

#include "Tools.h"
#include "Enum.h"

auto calculateCollision(GeometryBuffer* current_geometry, Ray* ray) -> float
{
	switch(current_geometry->type)
	{
		case EGeometry_type::SPHERE: 
		{
			SphereGeometryBuffer* derived = nullptr;
			derived = static_cast<SphereGeometryBuffer*> (current_geometry);
			return calculateSphereCollision(derived, ray);
		}break;

		default :
		{
			TriangleGeometryBuffer* derived = nullptr;
			derived = static_cast<TriangleGeometryBuffer*> (current_geometry);
			return calculateModelCollision(derived, ray);
		}break;
	}
	return -1.f;
}

auto calculateSphereCollision(SphereGeometryBuffer* current_geometry, Ray* ray) -> float
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
		return -1.f; // no colision
	
	else
	{
		//std::cout<<"Collision inside else"<<std::endl;
		float sqrt_discri = (float)(sqrt(discri));
		float t0 = (-B + sqrt_discri)/(2 * A);
		float t1 = (-B - sqrt_discri)/(2 * A);

		// We want the closest one 
		if (t0 > t1)
		    t0 = t1;

		// Verify t0 larger than 0 and less than the original t 
		if ((t0 > 0.001f) && (t0 < ray->lenght))
		    return t0;
	}
	return -1.f;	
}

auto calculateModelCollision(TriangleGeometryBuffer* current_geometry, Ray* ray) -> float
{
        std::vector<float> list_vertice = current_geometry->vertice_list;
	float t_coll = 100.f;
	int triangle_num = -1;

	for (unsigned int i = 0; i < list_vertice.size(); i += 9)
	{
		Vector3D<float> a = Vector3D<float>(list_vertice[i + 0], list_vertice[i + 1], list_vertice[i + 2]);
		Vector3D<float> b = Vector3D<float>(list_vertice[i + 3], list_vertice[i + 4], list_vertice[i + 5]);
		Vector3D<float> c = Vector3D<float>(list_vertice[i + 6], list_vertice[i + 7], list_vertice[i + 8]);
			a += current_geometry->position;
			b += current_geometry->position;
			c += current_geometry->position;

		Vector3D<float> ab_edge = (b - a);
		Vector3D<float> ac_edge = (c - a);
		Vector3D<float> p = ray->origin.normalize();
		Vector3D<float> d = ray->direction.normalize();

		Vector3D<float> h = (d * ac_edge);

		float _a = h.dot(ab_edge);
	 
		if (_a > -0.00001f && _a < 0.00001f)
			continue;

		float f = 1.f/_a;
		Vector3D<float> s = (p - a);
		float u = f * h.dot(s);

		if (u < 0.0f || u > 1.0f)
			continue;

		Vector3D<float> q = (s * ab_edge);
		float v = f * d.dot(q);

		if (v < 0.0f || u + v > 1.0f)
			continue;
	
		// at this stage we can compute t to find out where
		// the intersection point is on the line
		float t = f * q.dot(ac_edge);

		if (t > 0.00001f && t < t_coll) // ray intersection
		{
			triangle_num = i;
			t_coll = t;
		}
	}


	if (t_coll != 100.f)
	{
		if (current_geometry->coll_triangle != triangle_num)
		{
			current_geometry->coll_triangle = triangle_num;
//		std::cout << "coll_triangle : " << triangle_num << std::endl;
		}
		return t_coll;
	}

	return -1.f;
}

auto calculateCollisionPoint(float distance, Ray* ray) -> void
{
	ray->collision_point = (ray->direction * distance) + ray->origin;
}

auto isNodeBeforeLightSource(GeometryBuffer* current_node, std::vector<GeometryBuffer*> node_list, GeometryBuffer* light, Vector3D<float> coll_point) -> bool
{
	float dist_min = 100.f;
	GeometryBuffer* coll_geo = nullptr;

	Ray* ray = new Ray();
	ray->init(Eray_type::REFLECTION_RAY, light->position, 100.f, 100.f);
	ray->direction = coll_point - light->position;

	coll_geo = FindNearestCollision(node_list, ray, dist_min);

	delete ray;
	ray = nullptr;

	if (dist_min != 100.f)
	{
		if (coll_geo == current_node )
			return false;
		return true;
	}

	return false;
}

auto isCollisionWithNode(GeometryBuffer* current_node, std::vector<GeometryBuffer*> node_list, Ray* ray) -> GeometryBuffer*
{
	float dist_min = 100.f;
	GeometryBuffer* coll_geo = nullptr;

	coll_geo = FindNearestCollision(node_list, ray, dist_min);

	if (dist_min != 100.f)
	{
		if (coll_geo != current_node)
		{
			calculateCollisionPoint(dist_min, ray);
			return coll_geo;
		}
	}
	return nullptr;
}

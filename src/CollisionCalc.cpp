#include <cmath>
#include <iostream>
#include <cassert>

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
			SphereGeometryBuffer* derived_geometry = SphereCast(current_geometry);
			return calculateSphereCollision(derived_geometry, ray);
		}break;

		default :
		{
			TriangleGeometryBuffer* derived_geometry = TriangleCast(current_geometry);
			return calculateModelCollision(derived_geometry, ray);
		}break;
	}
	return -1.f;
}

auto calculateSphereCollision(SphereGeometryBuffer* current_geometry, Ray* ray) -> float
{
	Log* log = Log::getInstance();

	if(current_geometry == nullptr)
		log->error("Can't calculate collision. Reason: current_geometry is null.");

	Vector3D<float> circle_position = current_geometry->position;
	float circle_radius = current_geometry->radius;

	float A = ray->direction.dot(ray->direction);
	Vector3D<float> distance = ray->origin - circle_position;

	float B = 2 * ray->direction.dot(distance);

	float C = distance.dot(distance) - (circle_radius * circle_radius);

	float discriminant = B * B - 4 * A * C;

	if (discriminant < 0)
		return -1.f; // no colision
	
	else
	{
		//std::cout<<"Collision inside else"<<std::endl;
		float sqrt_discriminant = (float)(sqrt(discriminant));
		float t0 = (-B + sqrt_discriminant)/(2 * A);
		float t1 = (-B - sqrt_discriminant)/(2 * A);

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
	float ray_lenght = 100.f;
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
		Vector3D<float> ray_origin = ray->origin.normalize();
		Vector3D<float> ray_direction = ray->direction.normalize();

		Vector3D<float> h = (ray_direction * ac_edge);

		float determinant = h.dot(ab_edge);
	 
		if (determinant > -0.00001f && determinant < 0.00001f)
			continue;

		float inverse_determinant = 1.f/determinant;
		Vector3D<float> s = (ray_origin - a);
		float u = inverse_determinant * h.dot(s);

		if (u < 0.0f || u > 1.0f)
			continue;

		Vector3D<float> q = (s * ab_edge);
		float v = inverse_determinant * ray_direction.dot(q);

		if (v < 0.0f || u + v > 1.0f)
			continue;
	
		float distance = inverse_determinant * q.dot(ac_edge);

		if (distance > 0.00001f && distance < ray_lenght) 
		{
			triangle_num = i;
			ray_lenght = distance;
		}
	}


	if (ray_lenght != 100.f)
	{
		if (current_geometry->coll_triangle != triangle_num)
		{
			current_geometry->coll_triangle = triangle_num;
		}
		return ray_lenght;
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
	assert(ray);

	ray->init(Eray_type::REFLECTION_RAY, light->position, 100.f, 100.f, 1.0f);
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

#include <cmath>
#include <iostream>

#include "CollisionCalc.h"
#include "Vector.h"
#include "Log.h"

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

		case EGeometry_type::TRIANGLE:
		{
			TriangleGeometryBuffer* derived = nullptr;
			derived = static_cast<TriangleGeometryBuffer*> (current_geometry);
			return calculateTriangleCollision(derived, ray);
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

auto calculateTriangleCollision(TriangleGeometryBuffer* current_geometry, Ray* ray) -> float
{
	std::vector<float> _vertice = current_geometry->vertice_list;

        Vector3D<float> a = Vector3D<float>(_vertice[0], _vertice[1], _vertice[2]);
        Vector3D<float> b = Vector3D<float>(_vertice[3], _vertice[4], _vertice[5]);
        Vector3D<float> c = Vector3D<float>(_vertice[6], _vertice[7], _vertice[8]);
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
		return -1.f;

	float f = 1.f/_a;
	Vector3D<float> s = (p - a);
	float u = f * s.dot(h);

	if (u < 0.0f || u > 1.0f)
		return -1.f;

	Vector3D<float> q = (s * ab_edge);
	float v = f * d.dot(q);

	if (v < 0.0f || u + v > 1.0f)
		return -1.f;

	// at this stage we can compute t to find out where
	// the intersection point is on the line
	float t = f * q.dot(ac_edge);

	if (t > 0.00001f) // ray intersection
	{
		return t;
	}
	return -1.f;
}

auto calculateModelCollision(TriangleGeometryBuffer* current_geometry, Ray* ray) -> float
{
        std::vector<float> _vertice = current_geometry->vertice_list;
	float t_coll = 100.f;

	for (unsigned int i = 0; i < _vertice.size(); i += 9)
	{
		Vector3D<float> a = Vector3D<float>(_vertice[i + 0], _vertice[i + 1], _vertice[i + 2]);
		Vector3D<float> b = Vector3D<float>(_vertice[i + 3], _vertice[i + 4], _vertice[i + 5]);
		Vector3D<float> c = Vector3D<float>(_vertice[i + 6], _vertice[i + 7], _vertice[i + 8]);
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
			t_coll = t;
	}
	if (t_coll != 100.f)
		return t_coll;

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

//	float length = std::sqrt((coll_point - light->position).dot(coll_point - light->position));

//	std::cout << "length : " << length << std::endl;
//	std::cout << "current_node : " << current_node->position << std::endl;

	Ray* ray = new Ray();
	ray->init(Eray_type::REFLECTION_RAY, light->position, 100.f, 100.f);
	ray->direction = coll_point - light->position;

	for(unsigned int idx = 0; idx < node_list.size(); ++idx)
	{
		GeometryBuffer* temp_geo = node_list[idx];

		float res = calculateCollision(temp_geo, ray);

//	std::cout << "result : " << res << std::endl;

		if(res < dist_min && res > -1.f)
		{
			dist_min = res;
			coll_geo = temp_geo;
		}
	}	

//	std::cout << "dist_min : " << dist_min << std::endl;

	delete ray;
	ray = nullptr;

	if (coll_geo == current_node )
		return false;
	return true;
}

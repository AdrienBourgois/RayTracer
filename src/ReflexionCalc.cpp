#include <cmath>

#include "ReflexionCalc.h"
#include "MaterialBuffer.h"
#include "MathCalc.h"

auto calculateReflexion(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Ray* ray, unsigned int rebound) -> Vector3D<float>
{
	unsigned int max_rebound = 4;

	if (rebound < max_rebound)
	{
		Vector3D<float> normal;

		normal = normal.normalOnSphere(ray->collision_point, node->position) - node->position;

		Vector3D<float> ref_ray_dir = (ray->direction + normal) * 2.f;

		Ray *ref_ray = new Ray();
		ref_ray->init(Eray_type::REFLECTION_RAY, ray->collision_point, (ray->power * 0.75f), 100.f, 0, 1.f);
		ref_ray->direction = ref_ray_dir;

		if (ray->power > 10.f)
		{
			GeometryBuffer* coll_node = isCollisionWithNode(node, node_list, ref_ray);	
			if (coll_node)
			{
				Vector3D<float> ref_color = coll_node->material_buffer->color;
				++rebound;
				ref_color += calculateReflexion(coll_node, node_list, ref_ray, rebound);

				delete ref_ray;
				return ref_color;
			}
		}
	}
	return Vector3D<float>(0.f, 0.f, 0.f);
}

auto calcReflexion(GeometryBuffer* node, Ray* ray) -> Vector3D<float>
{
	Vector3D<float> normal;

	normal = normal.normalOnSphere(ray->collision_point, node->position) - node->position;
	Vector3D<float> ref_ray_dir = (ray->direction + normal) * 2.f;

	return ref_ray_dir;
}

auto calculateRefraction(GeometryBuffer* node, /*std::vector<GeometryBuffer*> node_list,*/ Ray* ray, float refraction_index) -> Vector3D<float>
{
	Vector3D<float> refracted_ray;
	
	Vector3D<float> incident_ray_direction_unit = ray->direction.normalize();
	Vector3D<float> normal = normal.normalOnSphere(ray->collision_point, node->position);

	float alpha = incident_ray_direction_unit.dot(normal);

	float N1 = ray->getCurrentMaterialRefractionIndex();
	float N2 = 0.f;
	if(refraction_index != -1.f)
		N2 = node->material_buffer->refraction_idx;
	else
		N2 = refraction_index;

	float Ni = N2 / N1;
		
	Vector3D<float> cosl = incident_ray_direction_unit * normal;
	Vector3D<float> cost = 1 - (1 / std::pow(Ni, 2)) * (1 - incident_ray_direction_unit * normal);
	refracted_ray = - ((1 / Ni) * incident_ray_direction_unit) - ((cost - (1 / Ni)) * cosl) * normal;


/*	float b = alpha * 2.f;

	float c = (1.f - std::pow((N2/N1), 2.f));

	Vector2D<float> koef = QuadraticEquation(1.f, b, c);
	float k = 0.f;

	if(koef.x == koef.y)
	{
		k = koef.x;
		refracted_ray = incident_ray_direction_unit + normal * k;
	}
	else
	{
		float res1 = 0.f;
		float res2 = 0.f;

		k = koef.x;
		Vector3D<float> refracted_ray_temp1 = incident_ray_direction_unit + (normal * k);
		res1 = ray->direction.dot(refracted_ray_temp1);
		
		k = koef.y;
		Vector3D<float> refracted_ray_temp2 = incident_ray_direction_unit + (normal * k);
		res2 = ray->direction.dot(refracted_ray_temp2);

		if(res1 > res2)
			refracted_ray = refracted_ray_temp1;
		else if(res2 > res1)
			refracted_ray = refracted_ray_temp2;
		if(res1 >= 0.f)
			refracted_ray = refracted_ray_temp1;
		else if(res2 >= 0.f)
			refracted_ray = refracted_ray_temp2;*/
	//}

	return refracted_ray;
}

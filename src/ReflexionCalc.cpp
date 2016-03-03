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
		ref_ray->init(Eray_type::REFLECTION_RAY, ray->collision_point, (ray->power * 0.75f), 100.f);
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

auto calculateRefraction(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Ray* ray) -> Vector3D<float>
{
	(void) node_list;
	Vector3D<float> refracted_ray;
	
	Vector3D<float> incident_ray_direction_unit = ray->direction.normalize();
	Vector3D<float> normal = normal.normalOnSphere(ray->collision_point, node->position);

	float alpha = incident_ray_direction_unit.dot(normal);

	float N1 = 1.3333f;
	float N2 = 1.5f;

	float b = alpha * 2;

	float c = (1 - std::pow((N2/N1), 2));

	Vector2D<float> koef = QuadraticEquation(1, b, c);
	float k = 0;

	if(koef.x == koef.y)
	{
		k = koef.x;
		refracted_ray = incident_ray_direction_unit + normal * k;
	}
	else
	{
		float res1 = 0;
		float res2 = 0;

		k = koef.x;
		Vector3D<float> refracted_ray_temp1 = incident_ray_direction_unit + normal * k;
		res1 = ray->direction.dot(refracted_ray_temp1);
		
		k = koef.y;
		Vector3D<float> refracted_ray_temp2 = incident_ray_direction_unit + normal * k;
		res2 = ray->direction.dot(refracted_ray_temp2);

		if(res1 > res2)
			refracted_ray = refracted_ray_temp1;
		else if(res2 > res1)
			refracted_ray = refracted_ray_temp2;
	}

		

	return normal;

}

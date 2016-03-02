#include "ReflexionCalc.h"
#include "MaterialBuffer.h"

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

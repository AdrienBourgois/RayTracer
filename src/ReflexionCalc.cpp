#include "ReflexionCalc.h"
#include "MaterialBuffer.h"
#include "MathCalc.h"
#include "Tools.h"

auto ReflectRay(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Ray* ray, unsigned int rebound) -> Vector3D<float>
{
	unsigned int max_rebound = 10;

	if (rebound < max_rebound)
	{
		Vector3D<float> normal;

		if (node->type == EGeometry_type::SPHERE)
			normal = Vector3D<float>::normalOnSphere(ray->collision_point, node->position);
		else
		{
			TriangleGeometryBuffer* derived = TriangleCast(node);
			normal = Vector3D<float>::normalOnModel(derived->vertice_list, derived->position, derived->coll_triangle);
		}	

		Vector3D<float> ray_dir = ray->direction.normalize();

		if (normal.dot(ray_dir) < 0.f)
		{
			
			Vector3D<float> refl_ray_dir = calculateReflexion(normal, ray_dir);
			Vector3D<float> refr_ray_dir = calculateRefraction(normal, ray_dir);

			Ray *refl_ray = new Ray();
			Ray *refr_ray = new Ray();
			refl_ray->init(Eray_type::REFLECTION_RAY, ray->collision_point, ray->power * 0.85f, 100.f);
			refr_ray->init(Eray_type::REFLECTION_RAY, ray->collision_point, ray->power * 0.85f, 100.f);
			refl_ray->direction = refl_ray_dir;
			GeometryBuffer* refl_coll_node = isCollisionWithNode(node, node_list, refl_ray);	
			refr_ray->direction = refr_ray_dir;
			GeometryBuffer* refr_coll_node = isCollisionWithNode(node, node_list, refr_ray);	
			Vector3D<float> ref_color;
			if (refl_coll_node)
			{
				ref_color += refl_coll_node->material_buffer->color * 0.1f;
				++rebound;
				ref_color += ReflectRay(refl_coll_node, node_list, refl_ray, rebound);
				
			}
			if (refr_coll_node)
			{
				ref_color += refr_coll_node->material_buffer->color * 0.1f;
				++rebound;
				ref_color += ReflectRay(refr_coll_node, node_list, refr_ray, rebound);
				
			}

			delete refl_ray;
			delete refr_ray;
			return ref_color;			
		}
	}
	return Vector3D<float>(0.f, 0.f, 0.f);
}

auto calculateReflexion(Vector3D<float> normal, Vector3D<float> ray_dir) -> Vector3D<float>
{
	float cl = normal.dot(ray_dir);
	Vector3D<float> ref_ray_dir = ray_dir - (normal * 2.f * cl);
	
	return ref_ray_dir.normalize();
}

auto calculateRefraction(Vector3D<float> normal, Vector3D<float> ray_dir) -> Vector3D<float>
{
	float cosI = -normal.dot(ray_dir);
	float cosT2 = 1.f - 0.3f * 0.3f * (1.f - cosI * cosI);
	Vector3D<float> ref_ray_dir;
	if (cosT2 > 0.f)
		ref_ray_dir = (ray_dir * 0.3f) + normal * (0.3f * cosI - std::sqrt(cosT2));

	return ref_ray_dir.normalize();
}

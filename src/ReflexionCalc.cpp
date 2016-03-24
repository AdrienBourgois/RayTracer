#include <cmath>

#include "ReflexionCalc.h"
#include "MaterialBuffer.h"
#include "MathCalc.h"
#include "Tools.h"

auto calculateReflexion(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Ray* ray, unsigned int rebound) -> Vector3D<float>
{
	unsigned int max_rebound = 10;

	if (rebound < max_rebound)
	{
		Vector3D<float> normal;

		if (node->type == EGeometry_type::SPHERE)
			normal = normalOnSphere(ray->collision_point, node->position);
		else
		{
			TriangleGeometryBuffer* derived = TriangleCast(node);
			normal = normalOnModel(derived->vertice_list, derived->position, derived->coll_triangle);
		}	

		Vector3D<float> ray_dir = ray->direction.normalize();

		if (normal.dot(ray_dir) < 0.f)
		{
			float cl = normal.dot(ray_dir);
			Vector3D<float> ref_ray_dir = ray_dir - (normal * 2.f * cl);
			
			ref_ray_dir = ref_ray_dir.normalize();
			Ray *ref_ray = new Ray();
			ref_ray->init(Eray_type::REFLECTION_RAY, ray->collision_point, ray->power * 0.85f, 100.f, 1.f);
			ref_ray->direction = ref_ray_dir;
			GeometryBuffer* coll_node = isCollisionWithNode(node, node_list, ref_ray);	
			if (coll_node)
			{
				Vector3D<float> ref_color = coll_node->material_buffer->color * 0.1f;
				++rebound;
				ref_color += calculateReflexion(coll_node, node_list, ref_ray, rebound);

				delete ref_ray;
				return ref_color;
			}
			delete ref_ray;
		}
	}
	return Vector3D<float>(0.f, 0.f, 0.f);
}

auto calculateRefraction(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Ray* ray, unsigned int rebound) -> Vector3D<float>
{
        unsigned int max_rebound = 10;

        if (rebound < max_rebound)
        {
                Vector3D<float> normal;

                if (node->type == EGeometry_type::SPHERE)
                        normal = normalOnSphere(ray->collision_point, node->position);
                else
                {
                        TriangleGeometryBuffer* derived = TriangleCast(node);
                        normal = normalOnModel(derived->vertice_list, derived->position, derived->coll_triangle);
                }

                Vector3D<float> ray_dir = ray->direction.normalize();

                if (normal.dot(ray_dir) < 0.f)
                {
			float cosI = -normal.dot(ray_dir);
			float cosT2 = 1.f - 0.3f * 0.3f * (1.f - cosI * cosI);
			Vector3D<float> ref_ray_dir;
			if (cosT2 > 0.f)
				ref_ray_dir = (ray_dir * 0.3f) + normal * (0.3f * cosI - std::sqrt(cosT2));

                        ref_ray_dir = ref_ray_dir.normalize();
                        Ray *ref_ray = new Ray();
                        ref_ray->init(Eray_type::REFLECTION_RAY, ray->collision_point, ray->power * 0.85f, 100.f, 1.f);
                        ref_ray->direction = ref_ray_dir;
                        GeometryBuffer* coll_node = isCollisionWithNode(node, node_list, ref_ray);
                        if (coll_node)
                        {
                                Vector3D<float> ref_color = coll_node->material_buffer->color * 0.1f;
                                ++rebound;
                                ref_color += calculateRefraction(coll_node, node_list, ref_ray, rebound);

                                delete ref_ray;
                                return ref_color;
                        }
                        delete ref_ray;
                }
	}
	return Vector3D<float>(0.f,0.f,0.f);
}

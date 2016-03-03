#include "LightCalc.h"

#include "CollisionCalc.h"
#include "ReflexionCalc.h"

auto calculateAmbiantLight(GeometryBuffer* node) -> Vector3D<float>
{
	Vector3D<float> node_color = node->material_buffer->color;

	float coef = 0.1f;
	Vector3D<float> color = node_color * coef;

	return color;
}

auto calculateDiffuseLight(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, std::vector<GeometryBuffer*> light, Ray* ray) -> Vector3D<float>
{
	if (light.size() == 0)	
		return Vector3D<float> {0.f, 0.f, 0.f};

	Vector3D<float> final_diffuse_color;
	for (unsigned int i = 0; i < light.size(); ++i)
	{
		if (!isNodeBeforeLightSource(node, node_list, light[i], ray->collision_point))
		{
			Vector3D<float> node_color = node->material_buffer->color;

			Vector3D<float> l =  (ray->collision_point - light[i]->position).normalize();
			Vector3D<float> normal;
			normal = normal.normalOnSphere(ray->collision_point, light[i]->position) - node->position;
			float shade = normal.dot(l.normalize()) * 0.35f;

			if (shade < 0.f)
				shade = 0.f;

			Vector3D<float> color;
			color.x = std::max((node_color.x - node_color.x * shade), 0.f);
			color.y = std::max((node_color.y - node_color.y * shade), 0.f);
			color.z = std::max((node_color.z - node_color.z * shade), 0.f);

			final_diffuse_color += color;
		}
		else
			final_diffuse_color += Vector3D<float> {0.f, 0.f, 0.f};
	}
	return final_diffuse_color;
}

auto calculateSpecularLight(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, std::vector<GeometryBuffer*> light, Ray* ray) -> Vector3D<float>
{
	if (light.size() == 0)  
		return Vector3D<float> {0.f, 0.f, 0.f};

	Vector3D<float> final_specular_light;
	for (unsigned int i = 0; i < light.size(); ++i)
	{
		if (!isNodeBeforeLightSource(node, node_list, light[i], ray->collision_point))
		{
			Vector3D<float> n;
			n = n.normalOnSphere(ray->collision_point, node->position) - node->position;
			n = n.normalize();
			Vector3D<float> l = (light[i]->position - ray->collision_point).normalize();
			Vector3D<float> v = (ray->origin - ray->collision_point).normalize();

			float nl = std::max(n.dot(l), 0.f); 
			Vector3D<float> r = (n * nl * 2.f) - l;

			r = r.normalize();
			Vector3D<float> specular_light = (light[i]->material_buffer->color * 0.70f);
			if (std::pow(r.dot(v) ,16.f) < 0.f)
				specular_light = specular_light * 0.f;
			else
				specular_light = specular_light * std::pow(std::max(r.dot(v), 0.f) ,16.f);
			
		    if (nl <= 0.0f)
				specular_light = specular_light * 0.0f;

			specular_light.normalize();

			final_specular_light += specular_light;
		}
		else
			final_specular_light += Vector3D<float> {0.f, 0.f, 0.f};
	}
	return final_specular_light;
}

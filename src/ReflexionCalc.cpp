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

		normal = normalOnSphere(ray->collision_point, node->position) - node->position;
		// WARN: may cause problem as normalOnSphere now return normalized vector

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

	normal = normalOnSphere(ray->collision_point, node->position) - node->position;
	// WARN: may cause problem as normalOnSphere now return normalized vector
	Vector3D<float> ref_ray_dir = (ray->direction + normal) * 2.f;

	return ref_ray_dir;
}

auto calculateRefraction(GeometryBuffer* node, /*std::vector<GeometryBuffer*> node_list,*/ Ray* ray, float refraction_index) -> Vector3D<float>
{
	Vector3D<float> refracted_ray;
	
	Vector3D<float> incident_ray_direction_unit = ray->direction.normalize();
	Vector3D<float> normal = normalOnSphere(ray->collision_point, node->position);

	//float alpha = incident_ray_direction_unit.dot(normal);
	//std::cout<<"node->material_buffer->refraction_idx = "<<node->material_buffer->refraction_idx<<std::endl;
	float N1 = ray->getCurrentMaterialRefractionIndex();
	float N2 = 0.f;
	//if(refraction_index == -1.f)
	//	N2 = node->material_buffer->refraction_idx;
	//else if (refraction_index != -1.f)
		N2 = refraction_index;
	//std::cout<<"N1 = "<<N1<<std::endl;
	//std::cout<<"N2 = "<<N2<<std::endl;

	float N_coeff = N1 / N2;
	N_coeff = 0.3f;
	//std::cout<<"Ni = "<<Ni<<std::endl;
	
	float cos_i = -1.0f * normal.dot(incident_ray_direction_unit);
	float cos_t2 = 1.0f - N_coeff * N_coeff * (1.0f - cos_i * cos_i);
	if (cos_t2 > 0.f)
	{
		refracted_ray = (incident_ray_direction_unit * N_coeff) + (normal *(N_coeff * cos_i - std::sqrt(cos_t2)));

		
	}

//	float N_coeff_squared = N_coeff*N_coeff;
/*
	float cos_incident_angle_squared = cos_incident_angle*cos_incident_angle;
	//std::cout<<"cosl = "<<cosl<<std::endl;
	//cosl = cosl * -1;
	//std::cout<<" - cosl = "<<cosl<<std::endl;
	//cosl = cosl * -1.f;
	//float cost = 1.f - Ni * Ni * (1.f - cosl - cosl);
	//float sint = Ni * Ni * (1.f - cosl * cosl); //////////
	//std::cout<<"sint = "<<sint<<std::endl;
	
	/*if (sint > 1.f)
	{
		return Vector3D<float>(0.f, 0.f, 0.f);
	}*//////////
	/*if (cost < 0)
		return Vector3D<float>(0.f, 0.f, 0.f);*/

	//float cost = std::sqrt(1.f - sint);/////////
	//std::cout<<"cost "<<cost<<std::endl;
	//refracted_ray = Ni * ray->direction + (Ni * cosl - cost) * normal;
	//refracted_ray = ray->direction * Ni + normal * (Ni * cosl - cost);//////////
	//std::cout<<"refracted_direction = "<<refracted_ray<<std::endl;
	//refracted_ray = (ray->direction * Ni) + (normal * (Ni * cosl - std::sqrt(cost)));
	//std::cout<<"HELLO"<<std::endl;

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
		{
			if(res1 > res2)
				refracted_ray = refracted_ray_temp1;
		}
		if(res2 >= 0.f)
		{
			if(res2 > res1)
				refracted_ray = refracted_ray_temp2;
		}
	}*/
	//std::cout<<"refracted_direction = "<<refracted_ray<<std::endl;
	return refracted_ray;
}

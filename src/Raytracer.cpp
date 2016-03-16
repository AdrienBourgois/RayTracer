#include <iostream>
//#include <SDL2/SDL.h>

#include "Raytracer.h"
#include "GeometryBuffer.h"
#include "MaterialBuffer.h"
#include "Ray.h"
#include "Log.h"
#include "MathCalc.h"
#include "CollisionCalc.h"
#include "LightCalc.h"

#include "ReflexionCalc.h"

typedef unsigned char uint8;

Raytracer::Raytracer()
{
	Log* log = Log::getInstance();
	log->info("Raytracer creation...");

	this->render_buffer.reset(new RenderBuffer);
	this->camera.reset(new Camera());
	this->camera_ray = new Ray();
	this->distance_min = 100.f;
	this->coll_result = 0.f;
	
	log->info("Raytracer created.");
}

Raytracer::~Raytracer()
{
	Log* log = Log::getInstance();
	log->info("Raytracer destroying...");

	this->render_buffer = nullptr;
	this->camera = nullptr;
	this->camera_ray = nullptr;

	log->info("Raytracer destroyed.");
}

auto Raytracer::init(Vector2D<float> rend_size) -> void
{
	Log* log = Log::getInstance();
	log->info("Raytracer initialization...");

	this->render_size = rend_size;

	this->camera->init();

	this->camera_ray->init(Eray_type::CAMERA_RAY, this->camera->position, 100.f, 1000.f, 0);

	log->info("Raytracer initialized.");
}

auto Raytracer::render() -> void
{
	GeometryBuffer* current_geometry = nullptr;
	(void) current_geometry;
	
	std::vector<GeometryBuffer*> light_list = this->genLightList();

	for (float idx_y = 0.f; idx_y < this->render_size.y; ++idx_y)
	{
		for(float idx_x = 0.f; idx_x < this->render_size.x; ++idx_x)
		{
			Vector3D<float> ray_dest_point = FindCameraRayDestinationPoint(this->render_size, idx_x, idx_y);

			this->camera_ray->direction = this->camera_ray->direction.direction(this->camera_ray->origin, ray_dest_point);
					
			//dist_min = 100.f;
			GeometryBuffer* collided_geometry = nullptr;
			//collision_result = 0.f;

				collided_geometry = searchForCollidedGeometry(this->camera_ray);

				if(collided_geometry != nullptr && !collided_geometry->material_buffer->is_light)
				{
					calculateCollisionPoint(this->distance_min, camera_ray);
				
					Vector3D<float> final_color;
					Vector3D<float> reflection_color;

					final_color += calculateAmbiantLight(collided_geometry);
					final_color += calculateDiffuseLight(collided_geometry, this->geometry_list, light_list, camera_ray->collision_point);
					final_color += calculateSpecularLight(collided_geometry, this->geometry_list, light_list, camera_ray);
					//reflection_color = calculateReflexion(collided_geometry, this->geometry_list, camera_ray, 0);
					reflection_color = recursiveReflection(collided_geometry);
					final_color += reflection_color;
					this->render_buffer->setColorList(final_color);
					this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
				}
				else if(collided_geometry != nullptr && collided_geometry->material_buffer->is_light)
				{
					this->render_buffer->setColorList(collided_geometry->material_buffer->color);
					this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
				}
				else if(collided_geometry == nullptr)
				{
					this->render_buffer->setColorList(Vector3D<float>(0.f,0.f,0.f));
					this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
				}
		}
	}
}

auto Raytracer::genGeometryBufferId() -> unsigned int
{
	 unsigned int id = 0;

	if (this->geometry_list.size() != 0)
		id += this->geometry_list[this->geometry_list.size() - 1]->getId() + 1;
	
	return id;
}

auto Raytracer::genGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list, EGeometry_type type_geometry, unsigned int id) -> void
{
	Log* log = Log::getInstance();
	log->info("Geometry buffer creation...");

	if (rad != 0.f)
	{
		GeometryBuffer* sphere_buffer = new SphereGeometryBuffer(pos, rad, vert_list, type_geometry, id);
		this->geometry_list.push_back(sphere_buffer);
	}

	else
	{
		GeometryBuffer* triangle_buffer = new TriangleGeometryBuffer(pos, vert_list, type_geometry, id);
		this->geometry_list.push_back(triangle_buffer);
	}

	log->info("Geometry buffer created.");
}

auto Raytracer::genMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light) -> void
{
	long unsigned int last_element = this->geometry_list.size() - 1u;
	this->geometry_list.at(last_element)->createMaterialBuffer(color_node, reflct_idx, refrct_idx, light);
}

auto Raytracer::genLightList() -> std::vector<GeometryBuffer*>
{
	std::vector<GeometryBuffer*> light_list;
	for (unsigned int i = 0; i < this->geometry_list.size(); ++i)
    {
	    if (this->geometry_list[i]->material_buffer->is_light)
        	light_list.push_back(this->geometry_list[i]);
	}
	
	return light_list;
}	

auto Raytracer::updateGeometryBuffer(unsigned int id, Vector3D<float> pos, Vector3D<float> col, float reflect_idx, float refract_idx) -> void
{
	GeometryBuffer* current_geometry_buffer = nullptr;

	for(unsigned int idx = 0; idx < this->geometry_list.size(); ++idx)
	{
		current_geometry_buffer = this->geometry_list[idx];
		if(current_geometry_buffer->getId() == id)
		{
			current_geometry_buffer->position = pos;
			current_geometry_buffer->material_buffer->color = col;
			current_geometry_buffer->material_buffer->reflection_idx = reflect_idx;
			current_geometry_buffer->material_buffer->refraction_idx = refract_idx;
		}
	}
}

auto Raytracer::searchForCollidedGeometry(Ray* ray) -> GeometryBuffer*
{
	GeometryBuffer* current_geometry = nullptr;
	GeometryBuffer* collided_geometry = nullptr;
	float dist_min = 100.f;
	float collision_result = 0.f;
// creare una variabile locale collision resul e passare in parametro il raggio attuale per non utilizzare sempre il raggio della camera
	for(unsigned int idx = 0; idx < this->geometry_list.size(); ++idx)
	{
		current_geometry = this->geometry_list[idx];
		collision_result = calculateCollision(current_geometry, ray);
		if(collision_result < dist_min && collision_result > -1.f)
		{
			dist_min = collision_result;
			collided_geometry = current_geometry;
		}
	}

	this->coll_result = collision_result;	
	this->distance_min = dist_min;
	return collided_geometry;
}

auto Raytracer::recursiveReflection(GeometryBuffer* geometry) -> Vector3D<float>
{
	GeometryBuffer* collided_geometry = geometry;
	float current_depth = 0.f;
	Vector3D<float> reflection_color;
	Ray* current_ray = camera_ray;
	while(current_depth < current_ray->max_depth && /*this->coll_result != -1.f*/ collided_geometry != nullptr)
	{
		++current_depth;
		Ray* reflection_ray = new Ray();
		reflection_ray->init(Eray_type::REFLECTION_RAY, current_ray->collision_point, 100.f, 1000.f, current_depth);
		reflection_ray->direction = calcReflexion(collided_geometry, current_ray);
		current_ray = reflection_ray;
		//std::cout<<"current_depth = "<<current_depth<<std::endl;	
//		this->collision_result = 0.f;
		collided_geometry = searchForCollidedGeometry(current_ray);
		if(collided_geometry != nullptr)
		{
			calculateCollisionPoint(this->distance_min, current_ray);
			reflection_color += collided_geometry->material_buffer->color;
		}
		//std::cout<<"inside while"<<std::endl;			
	}
	//if(current_depth > 0.f)
	//	std::cout<<"current_depth = "<<current_depth<<std::endl;
	return reflection_color;
}

auto Raytracer::close() -> void
{
	Log* log = Log::getInstance();
	log->info("Raytracer closing...");
	
	for(unsigned int idx = 0; idx < this->geometry_list.size(); ++idx)
	{
		this->geometry_list[idx]->close();
		delete this->geometry_list[idx];
	}
	this->geometry_list.clear();

	this->camera_ray->close();
	delete this->camera_ray;
	
	log->info("Raytracer closed.");
}

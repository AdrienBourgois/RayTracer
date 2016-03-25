#include <iostream>
#include <cassert>

#include "Raytracer.h"
#include "GeometryBuffer.h"
#include "MaterialBuffer.h"
#include "Ray.h"
#include "Log.h"
#include "MathCalc.h"
#include "CollisionCalc.h"
#include "LightCalc.h"
#include "Tools.h"
#include "ReflectionRefraction.h"

typedef unsigned char uint8;

Raytracer::Raytracer()
{
	Log* log = Log::getInstance();
	log->info("Raytracer creation...");

	this->render_buffer.reset(new RenderBuffer);
	this->camera.reset(new Camera());
	this->camera_ray = new Ray();
	assert(this->camera_ray);
	
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

	this->camera_ray->init(Eray_type::CAMERA_RAY, this->camera->position, 100.f, 1000.f, 1.0f);

	log->info("Raytracer initialized.");
}

auto Raytracer::render() -> void
{
	std::vector<GeometryBuffer*> light_list = extractLigthList();

	for (float idx_y = 0.f; idx_y < this->render_size.y; ++idx_y)
	{
		for(float idx_x = 0.f; idx_x < this->render_size.x; ++idx_x)
		{
			Vector3D<float> ray_dest_point = FindCameraRayDestinationPoint(this->render_size, idx_x, idx_y);

			this->camera_ray->direction = this->camera_ray->direction.direction(this->camera_ray->origin, ray_dest_point);
					
			float dist_min = 100.f;
			GeometryBuffer* collided_geometry = nullptr;
			collided_geometry = FindNearestCollision(this->geometry_list, camera_ray, dist_min);

			if (collided_geometry != nullptr && !collided_geometry->material_buffer->is_light)
			{
				calculateCollisionPoint(dist_min, camera_ray);
				Vector3D<float> final_color;
				final_color += calculateAmbiantLight(collided_geometry);
				final_color += calculateDiffuseLight(collided_geometry, this->geometry_list, light_list, camera_ray);
				final_color += calculateSpecularLight(collided_geometry, this->geometry_list, light_list, camera_ray);
				final_color += ReflectAndRefractRay(collided_geometry, this->geometry_list, camera_ray);
				
				this->render_buffer->setColorList(final_color);
				this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
			}
			else if (collided_geometry != nullptr && collided_geometry->material_buffer->is_light)
			{
				this->render_buffer->setColorList(Vector3D<float>(255.f,255.f,255.f));
				this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
			}
			else
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

auto Raytracer::genGeometryBuffer(Vector3D<float> position, float radius, std::vector<float> vertice_list, EGeometry_type type_geometry, unsigned int id) -> void
{
	Log* log = Log::getInstance();
	log->info("Geometry buffer creation...");

	if (radius != 0.f)
	{
		GeometryBuffer* sphere_buffer = new SphereGeometryBuffer(position, radius, vertice_list, type_geometry, id);
		assert(sphere_buffer);
		this->geometry_list.push_back(sphere_buffer);
	}
	else
	{
		GeometryBuffer* triangle_buffer = new TriangleGeometryBuffer(position, vertice_list, type_geometry, id);
		assert(triangle_buffer);
		this->geometry_list.push_back(triangle_buffer);
	}

	log->info("Geometry buffer created.");
}

auto Raytracer::genMaterialBuffer(Vector3D<float> color_node, float reflection_idx, float refraction_idx, bool light) -> void
{
	long unsigned int last_element = this->geometry_list.size() - 1u;
	this->geometry_list.at(last_element)->createMaterialBuffer(color_node, reflection_idx, refraction_idx, light);
}

auto Raytracer::updateGeometryBuffer(unsigned int id, Vector3D<float> position, Vector3D<float> color, float reflectn_idx, float refractn_idx) -> void
{
	GeometryBuffer* current_geometry_buffer = nullptr;

	for(unsigned int idx = 0; idx < this->geometry_list.size(); ++idx)
	{
		current_geometry_buffer = this->geometry_list[idx];

		if(current_geometry_buffer->getId() == id)
		{
			current_geometry_buffer->position = position;
			current_geometry_buffer->material_buffer->color = color;
			current_geometry_buffer->material_buffer->reflection_idx = reflectn_idx;
			current_geometry_buffer->material_buffer->refraction_idx = refractn_idx;
		}
	}
}

auto Raytracer::extractLigthList() -> std::vector<GeometryBuffer*>
{
	std::vector<GeometryBuffer*> light_list;
	GeometryBuffer* current_geometry = nullptr;
	for(unsigned int idx = 0; idx < this->geometry_list.size(); ++idx)
	{
		current_geometry = this->geometry_list[idx];
		
		if(current_geometry->material_buffer->is_light)
		{
			light_list.push_back(current_geometry);
		}
	}
	return light_list;
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

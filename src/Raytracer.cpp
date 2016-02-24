#include <iostream>
#include <SDL2/SDL.h>

#include "Raytracer.h"
#include "GeometryBuffer.h"
#include "MaterialBuffer.h"
#include "Ray.h"
#include "Log.h"
#include "MathCalc.h"
#include "CollisionCalc.h"

Raytracer::Raytracer()
{
	Log* log = Log::getInstance();
	log->info("Raytracer creation...");

	this->render_buffer.reset(new RenderBuffer);
	this->camera.reset(new Camera());
	this->camera_ray = new Ray();
	
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

	this->camera_ray->init(Eray_type::CAMERA_RAY, this->camera->position, 100.f, 1000.f);

	log->info("Raytracer initialized.");
}

auto Raytracer::render() -> void
{
	GeometryBuffer* current_geometry = nullptr;
	(void) current_geometry;

	for (float idx_y = 0.f; idx_y < this->render_size.y; ++idx_y)
	{
		for(float idx_x = 0.f; idx_x < this->render_size.x; ++idx_x)
		{
			Vector3D<float> ray_dest_point = FindCameraRayDestinationPoint(this->render_size, idx_x, idx_y);

			this->camera_ray->direction = ray_dest_point - this->camera_ray->origin;
		
			for(unsigned int idx = 0; idx < this->geometry_list.size(); ++idx)		 
			{
				current_geometry = this->geometry_list[idx];

				if(calculateCollision(current_geometry, camera_ray))
				{
					Vector3D<Uint8> color_value;
					color_value.x = Uint8 (current_geometry->material_buffer->color.x);
					color_value.y = Uint8 (current_geometry->material_buffer->color.y);
					color_value.z = Uint8 (current_geometry->material_buffer->color.z);

					this->render_buffer->setColorList(color_value);
					this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
				}
			}	
		}
	}
}

auto Raytracer::genGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list) -> void
{
	Log* log = Log::getInstance();
	log->info("Geometry buffer creation...");

	if (rad != 0.f)
	{
		SphereGeometryBuffer* sphere_buffer = new SphereGeometryBuffer(pos, rad, vert_list);
		this->geometry_list.push_back(sphere_buffer);
	}

	else
	{

	}

	log->info("Geometry buffer created.");
}

auto Raytracer::genMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light) -> void
{
	long unsigned int last_element = this->geometry_list.size() - 1u;
	this->geometry_list.at(last_element)->createMaterialBuffer(color_node, reflct_idx, refrct_idx, light);
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

	this->camera_ray->close();
	delete this->camera_ray;
	
	log->info("Raytracer closed.");
}

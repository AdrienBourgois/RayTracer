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
#include "Tools.h"

#include "ReflexionCalc.h"

typedef unsigned char uint8;

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
	std::vector<GeometryBuffer*> light_list;
	for (unsigned int i = 0; i < this->geometry_list.size(); ++i)
	{
		if (this->geometry_list[i]->material_buffer->is_light)
			light_list.push_back(this->geometry_list[i]);
	}

	for (float idx_y = 0.f; idx_y < this->render_size.y; ++idx_y)
	{
		for(float idx_x = 0.f; idx_x < this->render_size.x; ++idx_x)
		{
			Vector3D<float> ray_dest_point = FindCameraRayDestinationPoint(this->render_size, idx_x, idx_y);

			this->camera_ray->direction = this->camera_ray->direction.direction(this->camera_ray->origin, ray_dest_point);
					
				float dist_min = 100.f;
				GeometryBuffer* coll_geo = nullptr;

			coll_geo = FindNearestCollision(this->geometry_list, camera_ray, dist_min);

				if (coll_geo != nullptr && !coll_geo->material_buffer->is_light)
				{
					calculateCollisionPoint(dist_min, camera_ray);
					Vector3D<float> final_color;
					final_color += calculateAmbiantLight(coll_geo);
					final_color += calculateDiffuseLight(coll_geo, this->geometry_list, light_list, camera_ray);
					final_color += calculateSpecularLight(coll_geo, this->geometry_list, light_list, camera_ray);
			//////////////////////////
					final_color += calculateReflexion(coll_geo, this->geometry_list, camera_ray);
					final_color += calculateRefraction(coll_geo, this->geometry_list, camera_ray);
			/////////////////////////

					
					this->render_buffer->setColorList(final_color);
					this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
				}
				else if (coll_geo != nullptr && coll_geo->material_buffer->is_light)
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

template <typename T>
auto Raytracer::getGeometryPointer(GeometryBuffer* geometry_pointer) -> T*
{
	T* derived_class = nullptr;

	if (geometry_pointer->type == EGeometry_type::SPHERE)
	{
		derived_class = SphereCast(geometry_pointer);
		return derived_class;
	}
	return nullptr;
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

#include <iostream>

#include "Raytracer.h"
#include "Log.h"
#include "RenderBuffer.h"

Raytracer::Raytracer()
{
	Log* log = Log::getInstance();
	log->info("Raytracer creation...");

	this->render_buffer.reset(new RenderBuffer);
	this->camera.reset(new Camera());
	
	log->info("Raytracer created.");
}

Raytracer::~Raytracer()
{
	this->render_buffer = nullptr;
}

auto Raytracer::init(Vector2D<float> rend_size) -> void
{
	Log* log = Log::getInstance();
	log->info("Raytracer initialization...");

	this->render_size = rend_size;

	this->camera->init();

	log->info("Raytracer initialized.");
}

auto Raytracer::render() -> void
{

}

auto Raytracer::genGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list, bool light) -> void
{
	Log* log = Log::getInstance();
	log->info("Geometry buffer creation...");

	if (rad != 0.f)
		SphereGeometryBuffer* sphere_buffer = new SphereGeometryBuffer(pos, rad, vert_list, light);
		this->geometry_list.push_back(sphere_buffer);
	else
	{

	}

	log->info("Geometry buffer created.");
}

auto Raytracer::genMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx) -> void
{
	Log* log = Log::getInstance();
	log->info("Material buffer creation...");

	if(geometry_list.end()->material_buffer == nullptr)
	{
		geometry_list.end()->createMaterialBuffer(color_node, reflct_idx, refrct_idx);
		log->info("Material buffer created.");
	}

	else
		log->error("Can't create Material buffer. Reason: Material buffer exist already");
}

auto Raytracer::close() -> void
{

}


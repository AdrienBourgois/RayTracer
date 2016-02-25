#include "GeometryBuffer.h"
#include "MaterialBuffer.h"
#include "Log.h"

GeometryBuffer::~GeometryBuffer()
{
	Log* log = Log::getInstance();
	log->info("GeometryBuffer destroying...");

	this->material_buffer = nullptr;

	log->info("GeometryBuffer destroyed.");
}

auto GeometryBuffer::createMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light) -> void
{
	Log* log = Log::getInstance();
	log->info("Material buffer creation...");
	
	if(this->material_buffer == nullptr)
	{
		this->material_buffer = new MaterialBuffer(color_node, reflct_idx, refrct_idx, light);
		log->info("Material buffer created.");
	}
	
	else
		log->error("Can't create Material buffer. Reason: Material buffer exist already");
}

auto GeometryBuffer::close() -> void
{
	Log* log = Log::getInstance();
	log->info("GeometryBuffer closing...");
	
	delete this->material_buffer;

	log->info("GeometryBuffer closed.");
}

SphereGeometryBuffer::SphereGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list, EGeometry_type type_geometry)
{
	this->position = pos;
	this->radius = rad;
	this->vertice_list = vert_list;
	
	this->material_buffer = nullptr;
	this->type = type_geometry;
}

#include "GeometryBuffer.h"

SphereGeometryBuffer::SphereGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list, bool light)
{
	this->position = pos;
	this->radius = rad;
	this->vertice_list = vert_list;
	this->is_light = light;
	
	this->material_buffer = nullptr;
}

auto SphereGeometryBuffer::createMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx) -> void
{
	this->material_buffer = new MaterialBuffer(color_node, reflct_idx, refrct_idx);
}

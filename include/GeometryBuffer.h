#ifndef __GEOMETRYBUFFER_DECLARATION__
#define __GEOMETRYBUFFER_DECLARATION__

#include <memory>

#include "Vector.h"

struct GeometryBuffer
{
	GeometryBuffer() = default;
	~GeometryBuffer() = default;

	auto createMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx) -> void;

	Vector3D<float> 		position;

	std::vector<float> 		vertice_list;

	bool 					is_light;

	MaterialBuffer* 		material_buffer;
};




struct SphereGeometryBuffer() : public GeometryBuffer
{
	SphereGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list, bool light);
	~SphereGeometryBuffer() = default;

	float 					radius;
};

#endif

#ifndef __GEOMETRYBUFFER_DECLARATION__
#define __GEOMETRYBUFFER_DECLARATION__

#include <vector>

#include "Vector.h"

struct MaterialBuffer;

struct GeometryBuffer
{
	GeometryBuffer() = default;
	~GeometryBuffer();

	auto createMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light) -> void;

	auto close() -> void;

	Vector3D<float> 		position;

	std::vector<float> 		vertice_list;

	MaterialBuffer* 		material_buffer;
};




struct SphereGeometryBuffer : public GeometryBuffer
{
	SphereGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list);
	~SphereGeometryBuffer() = default;

	float 					radius;
};

#endif

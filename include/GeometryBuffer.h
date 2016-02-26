#ifndef __GEOMETRYBUFFER_DECLARATION__
#define __GEOMETRYBUFFER_DECLARATION__

#include <vector>

#include "Vector.h"
#include "Enum.h"

struct MaterialBuffer;

struct GeometryBuffer
{
	GeometryBuffer() = default;
	virtual ~GeometryBuffer();

	auto createMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light) -> void;

	auto close() -> void;

	Vector3D<float> 		position;

	std::vector<float> 		vertice_list;

	MaterialBuffer* 		material_buffer;

	EGeometry_type			type;

};




struct SphereGeometryBuffer : public GeometryBuffer
{
	SphereGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list, EGeometry_type type_geometry);
	~SphereGeometryBuffer() = default;

	float 					radius;
};

struct TriangleGeometryBuffer : public GeometryBuffer
{
	TriangleGeometryBuffer(Vector3D<float> pos, std::vector<float> vert_list, EGeometry_type type_geometry);
	~TriangleGeometryBuffer() = default;
};

#endif

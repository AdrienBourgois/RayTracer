#ifndef __GEOMETRYBUFFER_DECLARATION__
#define __GEOMETRYBUFFER_DECLARATION__

#include <memory>

#include "Vector.h"

struct GeometryBuffer
{
	GeometryBuffer() = default;
	~GeometryBuffer() = default;

	Vector3D<float> position;

	std::vector<float> vertice_list;

	bool is_light;

	MaterialBuffer* material_buffer;
};

struct SphereGeometryBuffer() : public GeometryBuffer
{
	SphereGeometryBuffer() = default;
	~SphereGeometryBuffer() = default;

	float radius;
};

#endif

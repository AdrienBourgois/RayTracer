#ifndef __GEOMETRYBUFFER_DECLARATION__
#define __GEOMETRYBUFFER_DECLARATION__

#include <vector>

#include "Vector.h"
#include "Enum.h"

struct MaterialBuffer;

struct GeometryBuffer
{
	GeometryBuffer() = default;
	GeometryBuffer(GeometryBuffer const&) = delete;
	GeometryBuffer(GeometryBuffer&&) = delete;
	virtual ~GeometryBuffer();

	auto operator =(GeometryBuffer const&) -> GeometryBuffer& = delete;
	auto operator =(GeometryBuffer&&) -> GeometryBuffer& = delete;

	auto createMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light) -> void;
 
	auto getId() -> unsigned int { return this->id; }

	auto close() -> void;

	Vector3D<float> 		position;

	std::vector<float> 		vertice_list;

	MaterialBuffer* 		material_buffer;

	EGeometry_type			type;

	protected:

		unsigned int 		id;
};




struct SphereGeometryBuffer : public GeometryBuffer
{
	SphereGeometryBuffer(Vector3D<float> position, float radius, std::vector<float> vertices_list, EGeometry_type type_geometry, unsigned int id_geometry_buffer);
	SphereGeometryBuffer(SphereGeometryBuffer const&) = delete;
	SphereGeometryBuffer(SphereGeometryBuffer&&) = delete;
	~SphereGeometryBuffer() = default;

	auto operator =(SphereGeometryBuffer const&) -> SphereGeometryBuffer& = delete;
	auto operator =(SphereGeometryBuffer&&) -> SphereGeometryBuffer& = delete;

	float 					radius;
};

struct TriangleGeometryBuffer : public GeometryBuffer
{
	TriangleGeometryBuffer(Vector3D<float> position, std::vector<float> vertices_list, EGeometry_type type_geometry, unsigned int id_geometry_buffer);
	TriangleGeometryBuffer(TriangleGeometryBuffer const&) = delete;
	TriangleGeometryBuffer(TriangleGeometryBuffer&&) = delete;
	~TriangleGeometryBuffer() = default;

	auto operator =(TriangleGeometryBuffer const&) -> TriangleGeometryBuffer& = delete;
	auto operator =(TriangleGeometryBuffer&&) -> TriangleGeometryBuffer& = delete;

	int coll_triangle = 0;
};

#endif

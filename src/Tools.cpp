#include "Tools.h"

auto FindNearestCollision(std::vector<GeometryBuffer*> node_list, Ray* ray, float &dist_min) -> GeometryBuffer*
{
	GeometryBuffer* coll_geo = nullptr;

	for(unsigned int idx = 0; idx < node_list.size(); ++idx)
	{
		GeometryBuffer* temp_geo = node_list[idx];

		float res = calculateCollision(temp_geo, ray);

		if(res < dist_min && res > -1.f)
		{
			dist_min = res;
			coll_geo = temp_geo;
		}
	}
	return coll_geo;
}

auto TriangleCast(GeometryBuffer* node) -> TriangleGeometryBuffer*
{
	TriangleGeometryBuffer* derived = nullptr;
//	derived = dynamic_cast<TriangleGeometryBuffer*> (node);
	derived = static_cast<TriangleGeometryBuffer*> (node);

	if (derived == nullptr)
		std::cerr << "derived = nullptr" << std::endl;

	return derived;
}

auto SphereCast(GeometryBuffer* node) -> SphereGeometryBuffer*
{
	SphereGeometryBuffer* derived = nullptr;
	derived = dynamic_cast<SphereGeometryBuffer*> (node);

	if (derived == nullptr)
		std::cerr << "derived = nullptr" << std::endl;

	return derived;
}


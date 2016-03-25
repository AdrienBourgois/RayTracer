#ifndef __MATERIALBUFFER_DECLARATION__
#define	__MATERIALBUFFER_DECLARATION__

#include "Vector.h"

struct MaterialBuffer
{
	MaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light);
	MaterialBuffer(MaterialBuffer const&) = delete;
	MaterialBuffer(MaterialBuffer&&) = delete;
	~MaterialBuffer() = default;

	auto operator =(MaterialBuffer const&) -> MaterialBuffer& = delete;
	auto operator =(MaterialBuffer&&) -> MaterialBuffer& = delete;

	Vector3D<float> color;

	float reflection_idx;
	float refraction_idx;
	
	bool is_light;	
};

#endif

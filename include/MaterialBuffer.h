#ifndef __MATERIALBUFFER_DECLARATION__
#define	__MATERIALBUFFER_DECLARATION__

#include "Vector.h"

struct MaterialBuffer
{
	MaterialBuffer() = default;
	~MaterialBuffer() = default;

	Vector3D<float> color;
	float reflection_idx;
	float refraction_idx;
};

#endif

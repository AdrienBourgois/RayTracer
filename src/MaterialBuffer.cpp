#include "MaterialBuffer.h"

MaterialBuffer::MaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx)
{
	this->color = color_node;
	this->reflection_idx = reflct_idx;
	this->refraction_idx = refrct_idx;
}

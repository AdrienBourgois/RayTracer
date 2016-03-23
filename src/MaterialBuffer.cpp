#include "MaterialBuffer.h"

MaterialBuffer::MaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light)
{
	std::cout<<"refrct_idx = "<<refrct_idx<<std::endl;
	this->color = color_node;

	this->reflection_idx = reflct_idx;
	this->refraction_idx = refrct_idx;
	std::cout<<"refractio_idx = "<<refraction_idx<<std::endl;

	this->is_light = light;
}

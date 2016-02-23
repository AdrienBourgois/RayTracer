#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__

#include <memory>

#include "Vector.h"

enum class ray_type
{
	CAMERA_RAY,
	REFLECTION_RAY,
	REFRACTION_RAY
} 

struct Ray
{
	public:
	
		Ray() = default;
		~Ray() = default;

	private:

		ray_type type;

		Vector3D<float> origin;
		Vector3D<float> direction;
		Vector3D<float> collision_point;
		float power;
		float lenght;
		
		std::vector<Ray*> child_list;
}

#endif

#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__

#include <vector>

#include "Vector.h"
#include "Enum.h"

struct Ray
{
	public:
	
		Ray();
		~Ray() = default;

		auto init(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray) -> void;
		auto close() -> void;


		Vector3D<float> origin;
		Vector3D<float> direction;
		Vector3D<float> collision_point;
		float power;
		float lenght;
		
	private:
		Eray_type type;
		std::vector<Ray*> child_list;
};

#endif

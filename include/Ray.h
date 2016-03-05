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

		auto init(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray, unsigned int depth) -> void;
		auto getCurrentDepth() -> unsigned int { return current_depth; }
		//auto createChild(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray) -> void;
		auto createChild(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray, unsigned int new_depth) -> Ray*;
		auto getType() -> Eray_type { return this->type;}
		auto getLastChildByType(Eray_type type_ray) -> Ray*;
		auto setDepth(unsigned int new_depth) -> void { this->current_depth = new_depth; }
		auto close() -> void;


		Vector3D<float> origin;
		Vector3D<float> direction;
		Vector3D<float> collision_point;
		float power;
		float lenght;
		unsigned int max_depth;
		
	private:
		Eray_type type;
		std::vector<Ray*> child_list;

		unsigned int current_depth;
};

#endif

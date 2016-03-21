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

		auto init(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray, unsigned int depth, float new_material_refraction_index) -> void;
		auto getCurrentDepth() -> unsigned int { return current_depth; }
		auto createChild(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray, unsigned int new_depth, float new_material_refraction_index) -> Ray*;
		auto getType() -> Eray_type { return this->type;}
		auto getLastChildByType(Eray_type type_ray) -> Ray*;
		auto getChildList() -> std::vector<Ray*> { return this->child_list; }
		auto getCurrentMaterialRefractionIndex() -> float { return this->current_material_refraction_index; }
		auto setDepth(unsigned int new_depth) -> void { this->current_depth = new_depth; }
		auto resetChildList() -> void;
		auto close() -> void;


		Vector3D<float> origin;
		Vector3D<float> direction;
		Vector3D<float> collision_point;
		float power;
		float lenght;
		unsigned int max_depth;
		float dist_min;
		float nearest_collision_distance;
		
	private:
		Eray_type type;
		std::vector<Ray*> child_list;

		unsigned int current_depth;
		
		float current_material_refraction_index;
};

#endif

#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__

#include <vector>

#include "Vector.h"
#include "Enum.h"

struct Ray
{
	public:
	
		Ray();
		Ray(Ray const&) = delete;
		Ray(Ray&&) = delete;
		~Ray() = default;

		auto operator =(Ray const&) -> Ray& = delete;
		auto operator =(Ray&&) -> Ray& = delete;

		auto init(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray, float new_material_refraction_index) -> void;
		auto close() -> void;

		auto getCurrentMaterialRefractionIndex() -> float { return this->current_material_refraction_index; }

		Vector3D<float> origin;
		Vector3D<float> direction;
		Vector3D<float> collision_point;
		float power;
		float lenght;
		
	private:
		Eray_type type;
		std::vector<Ray*> child_list;
		float current_material_refraction_index;
};

#endif

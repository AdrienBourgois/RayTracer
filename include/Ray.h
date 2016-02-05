#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__

#include <vector>

#include "Vector.h"

typedef unsigned char Uint8;

class Ray
{
public:
	Ray(Vector3D<float> _ray_origin, Vector3D<float> _ray_dir);
	~Ray() = default;

	auto getRayOrigin() -> Vector3D<float> {return this->ray_origin;}
	auto getRayDirection() -> Vector3D<float> {return this->ray_dir;}
	auto getRayMaxLenght() -> float {return this->dist_max;}

	auto setRayDirection(Vector3D<float> dir) -> void {this->ray_dir = dir;}
	auto setRayColor(std::vector<Uint8> ray_color) -> void;
	auto addColorToRay(std::vector<Uint8> color_to_add) -> void;
	auto getRayColor() -> std::vector<Uint8>;

private:
	Vector3D<float> ray_origin;
	Vector3D<float> ray_dir;
	float dist_max = 100.0f;
	Uint8 r_color, g_color, b_color;
};

#endif

#ifndef __CAMERA_DECLARATION__
#define __CAMERA_DECLARATION__

#include "Vector.h"

struct Camera
{
	Camera() = default;
	Camera(Camera const&) = delete;
	Camera(Camera&&) = delete;
	~Camera() = default;
	
	auto operator =(Camera const&) -> Camera& = delete;
	auto operator =(Camera&&) -> Camera& = delete;

	auto init() -> void;

	Vector3D<float> position;
	Vector3D<float> lookAt;
	Vector3D<float> viewDirection;
	Vector3D<float> u;
	Vector3D<float> v;
};

#endif

#ifndef __CAMERA_DECLARATION__
#define __CAMERA_DECLARATION__

#include "Vector.h"

class Camera
{
public:
	Camera();
	~Camera() = default;

    auto init(Vector2D<int> screen_res) -> void;

private:
	Vector3D<float> position;
    Vector3D<float> viewDirection;
    Vector3D<float> lookAt;
    Vector3D<float> up;
    Vector3D<float> u;
    Vector3D<float> v;
    Vector2D<int> screen_size;

    float FOV;
};

#endif

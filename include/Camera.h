#ifndef __CAMERA_DECLARATION__
#define __CAMERA_DECLARATION__

#include <memory>

#include "Vector.h"

class Ray;
class RenderBuffer;

class Camera
{
public:
	Camera();
	~Camera() = default;

    auto init(Vector2D<int> screen_res, RenderBuffer* rend_buffer) -> void;
    auto render() -> void;
    auto shot() -> void;

private:
    RenderBuffer* render_buffer;
	Vector3D<float> position;
    Vector3D<float> viewDirection;
    Vector3D<float> lookAt;
    Vector3D<float> up;
    Vector3D<float> u;
    Vector3D<float> v;
    Vector2D<float> screen_size;
    //Vector3D<float> coordNDC;
    Ray* ray;
    float FOV;
};

#endif

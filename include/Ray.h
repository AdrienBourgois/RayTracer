#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__

#include "Vector.h"

class RenderBuffer;

class Ray
{
public:
    
	Ray(Vector3D<float> position, Vector2D<float> screen_size, float idx_x, float idx_y, RenderBuffer* rend_buff);
	~Ray() = default;
    auto findDestPoint(Vector2D<float> screen_size, float idx_x, float idx_y) -> void;
    auto run(Vector2D<float> screen_size, float idx_x, float idx_y) -> void;

private:
    RenderBuffer* render_buffer;
	Vector3D<float> start_point;
    Vector3D<float> dest_point;
	Vector3D<float> direction;
	float dist_max;
};

#endif

#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__


#include <vector>

#include "Vector.h"

class RenderBuffer;
class SceneNode;

class Ray
{
public:
    
	Ray(Vector3D<float> position, Vector2D<float> screen_size, float idx_x, float idx_y, RenderBuffer* rend_buff, SceneNode* node);
	~Ray() = default;
    auto findDestPoint(Vector2D<float> screen_size, float idx_x, float idx_y) -> void;
    auto run(Vector2D<float> screen_size, float idx_x, float idx_y) -> void;

    auto collision() -> void;
private:
    RenderBuffer* render_buffer;

	Vector3D<float> start_point;
    Vector3D<float> dest_point;
	Vector3D<float> direction;

    SceneNode* scene_node;

	float lenght_max;

private:

};

#endif

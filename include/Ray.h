#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__


#include <vector>

#include "Vector.h"

class RenderBuffer;
class SceneNode;
class Driver;

class Ray
{
public:
    
	Ray(Vector3D<float> position, Vector2D<float> screen_res, RenderBuffer* rend_buff, SceneNode* node, Driver* drv);
	~Ray() = default;
    auto findDestPoint(float idx_x, float idx_y) -> void;
    auto findDirection() -> void;
    auto run() -> void;
    auto close() -> void;
    auto DOT(Vector3D<float> vector_1, Vector3D<float> vector_2) -> float;

    auto getDirection() -> Vector3D<float> {return this->direction;}
    auto getCollisionRes() -> bool { return this->collision_result; }
    auto getStartPoint() -> Vector3D<float> {return this->start_point;}
    auto getMaxLenght() -> float {return this->lenght_max;}

private:
    RenderBuffer* render_buffer;

    Vector2D<float> screen_size;
	Vector3D<float> start_point;
    Vector3D<float> dest_point;
	Vector3D<float> direction;

    SceneNode* scene_node;

    Driver* driver;

	float lenght_max;

    bool collision_result;
private:

};

#endif

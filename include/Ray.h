#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__


#include <vector>

#include "Vector.h"

class RenderBuffer;
class SceneNode;

class Ray
{
public:
    
	Ray(Vector3D<float> position, Vector2D<float> screen_res, RenderBuffer* rend_buff, std::vector<SceneNode*> node, bool child);
	Ray(Vector3D<float> position, /*Vector2D<float> screen_res, RenderBuffer* rend_buff,*/ std::vector<SceneNode*> node, bool child);
	~Ray() = default;
    auto findDestPoint(float idx_x, float idx_y) -> void;
    auto findDirection() -> void;
    auto run() -> void;

    auto runChild() -> void;
    auto collision(SceneNode* scene_node) -> bool;
    auto calculateReflexion(SceneNode* node) -> Vector3D<float>;
    auto calculateNormal(SceneNode* node) -> Vector3D<float>;
    auto calculateCollisionPoint(float distance) -> void;

    auto close() -> void;
    auto DOT(Vector3D<float> vector_1, Vector3D<float> vector_2) -> float;

    auto getDirection() -> Vector3D<float> {return this->direction;}
    auto getCollisionRes() -> bool { return this->collision_result; }
    auto getStartPoint() -> Vector3D<float> {return this->start_point;}
    auto getMaxLenght() -> float {return this->lenght_max;}

    auto setDirection(Vector3D<float> new_direction) -> void { this->direction = new_direction; }

private:
    RenderBuffer* render_buffer;

    Vector2D<float> screen_size;
	Vector3D<float> start_point;
    Vector3D<float> dest_point;
	Vector3D<float> direction;
    Vector3D<float> collision_point;
	Vector3D<float> color_value;

    std::vector<SceneNode*> node_list;
    std::vector<Ray*>       child_list;

	float lenght_max;
    float power;

    bool collision_result;
    bool is_child;

};

#endif

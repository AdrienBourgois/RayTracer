#ifndef __COLLISION_DECLARATION__
#define __COLLISION_DECLARATION__

#include "Vector.h"

class Ray;
class SceneNode;

class Collision
{
public:
	Collision() = default;
	~Collision() = default;

	auto rayCircleCollision(Ray ray, SceneNode circle) -> bool;
	auto rayPlaneCollision(Ray ray, SceneNode plane) -> bool;
private:
};

#endif

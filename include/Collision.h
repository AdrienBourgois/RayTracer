#ifndef __COLLISION_DECLARATION__
#define __COLLISION_DECLARATION__

class Ray;
class SceneNode;

class Collision
{
public:
	Collision() = default;
	~Collision() = default;

	auto rayCircleCollision(Ray ray, SceneNode circle) -> bool;
private:

};

#endif

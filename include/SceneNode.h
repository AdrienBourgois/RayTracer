#ifndef __SCENENODE_DECLARATION__
#define __SCENENODE_DECLARATION__

#include <vector>
#include <SDL2/SDL.h>

#include "Vector.h"

enum class ModelType
{
	TRIANGLE,
	PLANE,
	SPHERE
};

class SceneNode
{
public:
	SceneNode(ModelType kind, bool light) {this->init(kind, light, 3.f);}
	SceneNode(ModelType kind, bool light, float rad) {this->init(kind, light, rad);}
	~SceneNode() = default;
	
	auto init(ModelType kind, bool light, float rad) -> void;

	auto setPosition(const Vector3D<float> value) -> void {this->position += value;}
	auto setPosition(float x, float y, float z) -> void;
	auto setRotation(const Vector3D<float> value) -> void {this->rotation += value;}
	auto setScale(const Vector3D<float> value) -> void {this->scale += value;}

	auto getPosition() const -> Vector3D<float> {return this->position;}
	auto getRotation() const -> Vector3D<float> {return this->rotation;}
	auto getScale() const -> Vector3D<float> {return this->scale;}

	auto getVertice() const -> std::vector<float> {return this->vertice;}
	auto getVerticeSize() -> unsigned int {return (unsigned int)this->vertice.size();}

	auto getRadius() -> float;
	auto getNodeType() -> ModelType {return this->type;}

	auto getRectAPoint() -> Vector3D<float>;
	auto getRectBPoint() -> Vector3D<float>;
	auto getRectCPoint() -> Vector3D<float>;

    auto getReflectionIdx() -> float { return this->reflection_idx; }
	auto getIsLight() -> bool { return this->is_light; }
	auto getColor() -> Vector3D<Uint8> { return this->color; }

private:
	ModelType type;
	std::vector<float> vertice;
	Vector3D<float> position;
	Vector3D<float> rotation;
	Vector3D<float> scale;
	Vector3D<Uint8> color;

    	float reflection_idx;

	float radius;	
	bool  is_light;
};

#endif

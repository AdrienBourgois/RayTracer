#ifndef __SCENENODE_DECLARATION__
#define __SCENENODE_DECLARATION__

#include "Matrix.h"
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
	SceneNode(ModelType kind) {this->init(kind);}
	~SceneNode();
	
	auto init(ModelType kind) -> void;

	auto setPosition(const Vector3D<float> value) -> void {this->position += value;}
	auto setRotation(const Vector3D<float> value) -> void {this->rotation += value;}
	auto setScale(const Vector3D<float> value) -> void {this->scale += value;}

	auto getPosition() const -> Vector3D<float> {return this->position;}
	auto getRotation() const -> Vector3D<float> {return this->rotation;}
	auto getScale() const -> Vector3D<float> {return this->scale;}

	auto getMatrix() const -> Matrix4x4;

private:
	ModelType type;
	std::vector<float> vertice;
	Vector3D<float> position;
	Vector3D<float> rotation;
	Vector3D<float> scale;
	
};

#endif

#include "SceneNode.h"

auto SceneNode::init(ModelType kind) -> void
{

	switch(kind)
	{
		case ModelType::TRIANGLE :
		this->vertice = {
		0.f, 0.f, 0.f,         1.f, 1.f, 1.f,
		0.f, -1.f, 0.f,         1.f, 1.f, 1.f,
		1.f, 0.f, 0.f,         1.f, 1.f, 1.f
		}; break;

		case ModelType::PLANE :
		this->vertice = {
		0.f, 0.f, 0.f,         1.f, 1.f, 1.f,
		0.f, -1.f, 0.f,         1.f, 1.f, 1.f,
		1.f, 0.f, 0.f,         1.f, 1.f, 1.f,

		0.f, -1.f, 0.f,         1.f, 1.f, 1.f,
		1.f, -1.f, 0.f,         1.f, 1.f, 1.f,
		1.f, 0.f, 0.f,         1.f, 1.f, 1.f
		}; break;
	
		case ModelType::SPHERE :
		break;

		default :
		this->vertice = {
		0.f, 0.f, 0.f,         1.f, 1.f, 1.f,
		0.f, 0.f, 0.f,         1.f, 1.f, 1.f,
		0.f, 0.f, 0.f,         1.f, 1.f, 1.f
		}; break;
	}

	this->position = Vector3D<float>(0.f, 0.f, 0.f);
	this->rotation = Vector3D<float>(0.f, 0.f, 0.f);
	this->scale = Vector3D<float>(1.f, 1.f, 1.f);
}

auto SceneNode::getMatrix() const -> Matrix4x4
{
	Matrix4x4 matrix = Matrix4x4::identity;

	matrix *= Matrix4x4::identity.tanslate(this->position);
	matrix *= Matrix4x4::identity.rotate(this->rotation);
	matrix *= Matrix4x4::identity.scale(this->scale);

	return matrix;	
}


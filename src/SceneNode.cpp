#include <math.h>
#include <iostream>

#include "SceneNode.h"

auto SceneNode::init(ModelType kind) -> void
{
	this->position = Vector3D<float>(0.f, 0.f, 0.f);
	this->rotation = Vector3D<float>(0.f, 0.f, 0.f);
	this->scale = Vector3D<float>(1.f, 1.f, 1.f);

	switch(kind)
	{
		case ModelType::TRIANGLE:
		this->type = ModelType::TRIANGLE;
		this->vertice = {
		0.f, 0.f, 0.f,
		0.f, -1.f, 0.f,
		1.f, 0.f, 0.f,
		}; break;

		case ModelType::PLANE:
		this->type = ModelType::PLANE;
		this->vertice = {
		0.f, 0.f, 0.f,
		0.f, -1.f, 0.f,
		1.f, 0.f, 0.f,

		0.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		1.f, 0.f, 0.f,
		}; break;
	
		case ModelType::SPHERE:
		{
		this->type = ModelType::SPHERE;
		this->radius = 3.0f;
		double r = (double)this->radius;

		for (double phi = 0.; phi < 2*M_PI; phi += M_PI/10.) // Azimuth [0, 2PI]
		{
			for (double theta = 0.; theta < M_PI; theta += M_PI/10.) // Elevation [0, PI]
			{
			    vertice.push_back((float)(r * cos(phi) * sin(theta)) + position.x);
			    vertice.push_back((float)(r * sin(phi) * sin(theta)) + position.y);
			    vertice.push_back((float)(r * cos(theta)) + position.z);
			}
		}

		break;
		}

		default:
		this->vertice = {
		0.f, 0.f, 0.f,
		0.f, 0.f, 0.f,
		0.f, 0.f, 0.f,
		}; break;
	}
}

auto SceneNode::getMatrix() const -> Matrix4x4
{
	Matrix4x4 matrix = Matrix4x4::identity;

	matrix *= Matrix4x4::identity.translate(this->position);
	matrix *= Matrix4x4::identity.rotate(this->rotation);
	matrix *= Matrix4x4::identity.scale(this->scale);

	return matrix;	
}

auto SceneNode::getRadius() -> float
{
	if (this->type == ModelType::SPHERE)
		return this->radius;

	else
	{
		std::cerr << "This is not a shpere" << std::endl;
		return 0.f;
	}
}


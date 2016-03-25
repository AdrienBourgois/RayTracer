#include "math.h"

#include "SceneNode.h"
#include "Model.h"

SceneNode::SceneNode(Raytracer* raytrace)
{
	this->reflection_idx = 0.f;
	this->refraction_idx = 0.f;
	this->radius = 0.f;
	this->is_light = false;
	this->geometry_buffer_id = 0;
	
	this->raytracer = raytrace;
}

auto SceneNode::init(Vector3D<float> position, Vector3D<float> color, bool light, float radius, EGeometry_type type) -> void
{
	this->position = position;
	this->radius = radius;
	this->color = color;
	this->is_light = light;

	this->reflection_idx = 100.f;

	double rad = static_cast<double>(this->radius);
	switch (type)
	{
	case EGeometry_type::SPHERE :
	{
	    for (double phi = 0.; phi < 2*M_PI; phi += M_PI/10.) // Azimuth [0, 2PI]
	    {
		for (double theta = 0.; theta < M_PI; theta += M_PI/10.) // Elevation [0, PI]
		{
		    vertice.push_back(static_cast<float>(rad * cos(phi) * sin(theta)) + position.x);
		    vertice.push_back(static_cast<float>(rad * sin(phi) * sin(theta)) + position.y);
		    vertice.push_back(static_cast<float>(rad * cos(theta)) + position.z);
		}
	    }
	}break;

	case EGeometry_type::TRIANGLE :
	{
		vertice = {
		1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f,
		-1.f, -1.f, 0.f
		};
	}break;

	case EGeometry_type::MODEL :
	{
		Model model = Model();
		model.loadFile("chara.obj");
		vertice = model.getMesh();
	}break;
	
	default : 
	{
		vertice = {
                0.f, 0.f, 0.f,
                -1.f, 0.f, 0.f,
                -1.f, -1.f, 0.f,

                0.f, 0.f, 0.f,
		-1.f, -1.f, 0.f,
                0.f, -1.f, 0.f,

		0.f, 0.f, 0.f,
		0.f, 1.f, -1.f,
		-1.f, 0.f, 0.f,

		0.f, 0.f, 0.f,
		1.f, 1.f, -1.f,
		0.f, 1.f, -1.f,

		0.f, 0.f, 0.f,
		0.f, -1.f, 0.f,
		1.f, 1.f, -1.f,

		1.f, 1.f, -1.f,
		0.f, -1.f, 0.f,
		1.f, 0.f, -1.f,
              };
	}break;

	}
}

auto SceneNode::draw() -> void
{
	raytracer->updateGeometryBuffer(this->geometry_buffer_id, this->position, this->color, this->reflection_idx, this->refraction_idx);
}

auto SceneNode::setPosition(Vector3D<float> position) -> void
{
	this->position = position;
}

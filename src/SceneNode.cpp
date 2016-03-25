#include "math.h"

#include "SceneNode.h"
#include "Model.h"

SceneNode::SceneNode(Raytracer* raytrace)
{
	this->reflection_idx = 0.f;
	this->refraction_idx = 1.31f;
	this->radius = 0.f;
	this->is_light = false;
	this->geometry_buffer_id = 0;
	
	this->raytracer = raytrace;
}

auto SceneNode::init(Vector3D<float> pos, Vector3D<float> col, bool light, float rad, EGeometry_type type) -> void
{
	this->position = pos;
	this->radius = rad;
	this->color = col;
	this->is_light = light;

	this->reflection_idx = 100.f;

	double r = static_cast<double>(this->radius);
	switch (type)
	{
	case EGeometry_type::SPHERE :
	{
	    for (double phi = 0.; phi < 2*M_PI; phi += M_PI/10.) // Azimuth [0, 2PI]
	    {
		for (double theta = 0.; theta < M_PI; theta += M_PI/10.) // Elevation [0, PI]
		{
		    vertice.push_back(static_cast<float>(r * cos(phi) * sin(theta)) + position.x);
		    vertice.push_back(static_cast<float>(r * sin(phi) * sin(theta)) + position.y);
		    vertice.push_back(static_cast<float>(r * cos(theta)) + position.z);
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
		model.loadFile("Bread.obj");
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

auto SceneNode::setPosition(Vector3D<float> pos) -> void
{
	this->position = pos;
}

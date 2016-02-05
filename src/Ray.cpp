#include "Ray.h"

Ray::Ray(Vector3D<float> _ray_origin, Vector3D<float> _ray_dir)
{
	this->ray_origin = _ray_origin;
	this->ray_dir = _ray_dir;

	this->r_color = this->g_color = this->b_color = 0;
}

auto Ray::setRayColor(std::vector<Uint8> ray_color) -> void
{
	this->r_color = ray_color[0];
	this->g_color = ray_color[1];
	this->b_color = ray_color[2];
}

auto Ray::addColorToRay(std::vector<Uint8> color_to_add) -> void
{
	if (this->r_color != 255)
		this->r_color = (Uint8)(this->r_color + color_to_add[0]);

	if (this->g_color != 255)
		this->g_color = (Uint8)(this->g_color + color_to_add[1]);

	if (this->b_color != 255)
		this->b_color = (Uint8)(this->b_color + color_to_add[2]);
}

auto Ray::getRayColor() -> std::vector<Uint8>
{
	std::vector<Uint8> result;

	result.push_back(this->r_color);
	result.push_back(this->g_color);
	result.push_back(this->b_color);

	return result;
}

#include "Ray.h"
#include "Log.h"

Ray::Ray()
{
	this->type = Eray_type::CAMERA_RAY;
	this->power = 0.f;
	this->lenght = 0.f;
	this->max_depth = 0;
	this->current_depth = 0;
}

auto Ray::init(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray) -> void
{
	this->type = type_ray;
	this->origin = origin_ray;
	this->power = power_ray;
	this->lenght = lenght_ray;
}

auto Ray::close() -> void
{
	Log* log = Log::getInstance();
	log->info("Ray closing...");

	for(unsigned int idx = 0; idx < child_list.size(); ++idx)
	{
		this->child_list[idx]->close();
		delete this->child_list[idx];
	}

	log->info("Ray closed.");
}

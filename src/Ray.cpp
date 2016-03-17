#include "Ray.h"
#include "Log.h"

Ray::Ray()
{
	this->type = Eray_type::CAMERA_RAY;
	this->power = 0.f;
	this->lenght = 0.f;
	this->max_depth = 4;
	this->current_depth = 0;
	this->dist_min = 100.f;
	this->nearest_collision_distance = 0.f;
}

auto Ray::init(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray, unsigned int depth) -> void
{
	this->type = type_ray;
	this->origin = origin_ray;
	this->power = power_ray;
	this->lenght = lenght_ray;
	this->current_depth = depth;
}

auto Ray::createChild(Eray_type type_ray, Vector3D<float> origin_ray, float power_ray, float lenght_ray, unsigned int new_depth) -> Ray*
{
	Ray* child_ray = new Ray();
	child_ray->init(type_ray, origin_ray, power_ray, lenght_ray, new_depth);
	child_list.push_back(child_ray);
	
	return child_ray;
}

auto Ray::getLastChildByType(Eray_type type_ray) -> Ray*
{
	Ray* current_child = nullptr;
	if(this->child_list.size() == 0 && this->type == Eray_type::REFLECTION_RAY)
		current_child = this;
	else
	{
		for(unsigned int idx = 0; idx < this->child_list.size(); ++idx)
		{
			current_child = this->child_list[idx]->getLastChildByType(type_ray);
		}
	}
	return current_child;
}

auto Ray::resetChildList() -> void
{
	if(child_list.size() > 0)
	{
		for(unsigned int idx = 0; idx < child_list.size(); ++idx)
    	{   
        	this->child_list[idx]->resetChildList();
        	delete this->child_list[idx];
			child_list.erase(child_list.begin() + idx);
    	}
	}
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

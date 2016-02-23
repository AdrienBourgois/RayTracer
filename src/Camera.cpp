#include "Camera.h"
#include "Log.h"

auto Camera::init() -> void
{
	Log* log = Log::getInstance();
	log->info("Camera initializing...");
	
	Vector3D<float> up = Vector3D<float>(0.f, 1.f, 0.f);
	
	this->position = Vector3D<float>(0.f, 0.f, 1.0f);
	this->viewDirection = this->lookAt - this->position;
	this->u = this->viewDirection * up;
	this->v = this->u * this->viewDirection;

	log->info("Camera created and initialized.");
}

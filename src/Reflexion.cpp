#include "Reflexion.h"

#include "Vector.h"
#include "Log.h"

Reflexion::Reflexion()
{
    Log* log = Log::getInstance();
    log->info("Reflexion creation...");

	this->originalRay 	= Vector3D<float> (0.f, 0.f, 0.f);
	this->reflexionRay  = Vector3D<float> (0.f, 0.f, 0.f);
	this->refractionRay = Vector3D<float> (0.f, 0.f, 0.f);
	this->normal		= Vector3D<float> (0.f, 0.f, 0.f);

    log->info("Reflexion created.");
}

Reflexion::~Reflexion()
{

    Log* log = Log::getInstance();
    log->info("Reflexion destroying...");
	
	this->originalRay   = nullptr;
	this->reflexionRay  = nullptr;
	this->refractionRay = nullptr;
	this->normal 		= nullptr;
   
	log->info("Reflexion destroyed.");
}

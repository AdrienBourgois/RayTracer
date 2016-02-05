#include "Reflexion.h"

#include "Vector.h"
#include "Log.h"

Reflexion::Reflexion()
{
    Log* log = Log::getInstance();
    log->info("Reflexion creation...");

	this->outputDir = Vector3D<float> (0.f, 0.f, 0.f);
	this->inputDir  = Vector3D<float> (0.f, 0.f, 0.f);
	this->normal	= Vector3D<float> (0.f, 0.f, 0.f);

    log->info("Reflexion created.");
}

Reflexion::~Reflexion()
{

    Log* log = Log::getInstance();
    log->info("Reflexion destroying...");
	
	this->outputDir = nullptr;
	this->inputDir = nullptr;
	this->normal = nullptr;
   
	log->info("Reflexion destroyed.");
}

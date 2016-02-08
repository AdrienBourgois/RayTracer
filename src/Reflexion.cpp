#include "Reflexion.h"

#include "Vector.h"
#include "Log.h"

Reflexion::Reflexion()
{
    Log* log = Log::getInstance();
    log->info("Reflexion creation...");

	this->oriMedium		= 1.0f;
	this->newMedium		= 1.49f;
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

Reflexion::calculateReflexion()		->	void
{
	this->reflexionCalc		= -dot_product(this->normal, this->originalRay);

	this->reflexionRay		= this->originalRay + (2 * this->normal * this->reflexionCalc);
}

Reflexion::calculateRefraction()	->	void
{
	float	indRefraction	= this->oriMedium / this->newMedium;

	this->refractionCalc 	= sqrt( 1 - pow(indRefraction, 2) * (1 - pow(this->reflexionCalc, 2)));

	this->refractionRay		= (indRefraction * this->originalRay) + (indRefraction * this->reflexionRay - this->refractionRay) * this->normal;
}

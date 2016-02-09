#include "Reflexion.h"

#include "Vector.h"
#include "Log.h"

#include <vector>
#include <cmath>

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
	this->indRefraction	= 0.f;

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

auto	Reflexion::dot_product(Vector3D<float> vec1, Vector3D<float> vec2)	->float	
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

auto	Reflexion::calculateReflexion()		->	void
{
	this->reflexionCalc		= -dot_product(this->normal, this->originalRay);

	this->reflexionRay		= this->originalRay + (this->normal * this->reflexionCalc * 2.f);
}

auto	Reflexion::calculateRefraction()	->	void
{
	this->indRefraction		= this->oriMedium / this->newMedium;

	float res1 = static_cast<float>(pow(indRefraction, 2));
	float res2 = 1.f - static_cast<float>(pow(reflexionCalc, 2));

	this->refractionCalc 	= static_cast<float>(sqrt(1.f - res1 * res2));

	this->refractionRay		= (this->originalRay * this->indRefraction) + (this->reflexionRay * this->indRefraction - this->refractionCalc) * this->normal;
}

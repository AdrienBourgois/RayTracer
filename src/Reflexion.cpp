#include "Reflexion.h"

#include "Vector.h"
#include "Log.h"

#include <vector>
#include <iostream>
#include <cmath>

Reflexion::Reflexion()
{
    Log* log = Log::getInstance();
    log->info("Reflexion creation...");

	this->oriMedium		 = 1.0f;
	this->newMedium		 = 1.49f;
	this->indRefraction	 = 0.f;
	this->reflexionCalc	 = 0.f;
	this->refractionCalc = 0.f;
	this->originalRay 	 = Vector3D<float> (-4.f, 4.f, 6.f);
	this->reflexionRay   = Vector3D<float> (0.f, 0.f, 0.f);
	this->refractionRay  = Vector3D<float> (0.f, 0.f, 0.f);
	this->normal		 = Vector3D<float> (0.f, 1.f, 0.f);

    log->info("Reflexion created.");
}

Reflexion::~Reflexion()
{

    Log* log = Log::getInstance();
    log->info("Reflexion destruction...");
	
	this->oriMedium		 = 0.f;
	this->newMedium		 = 0.f;
	this->indRefraction	 = 0.f;
	this->reflexionCalc	 = 0.f;
	this->refractionCalc = 0.f;
	this->originalRay    = nullptr;
	this->reflexionRay   = nullptr;
	this->refractionRay  = nullptr;
	this->normal 		 = nullptr;
   
	log->info("Reflexion destructed.");
}

auto	Reflexion::init()	->	void
{
}

auto	Reflexion::dot_product(Vector3D<float> vec1, Vector3D<float> vec2)	->float	
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

auto	Reflexion::calculateReflexion()		->	void
{
	this->reflexionCalc	= -dot_product(this->normal, this->originalRay);

	std::cout << "ReflexionCalc = " << this->reflexionCalc << std::endl;

	this->reflexionRay = this->originalRay + (this->normal * this->reflexionCalc * 2.f);

	std::cout << "ReflexionRay = " << this->reflexionRay << std::endl;
}

auto	Reflexion::calculateRefraction()	->	void
{
	this->indRefraction	= this->oriMedium / this->newMedium;

	std::cout << "IndRefraction = " << this->indRefraction << std::endl;

	float res1 = static_cast<float>(pow(indRefraction, 2));
	float res2 = 1.f - static_cast<float>(pow(reflexionCalc, 2));

	this->refractionCalc = static_cast<float>(sqrt(1.f - res1 * res2));

	std::cout << "RefractionCalc = " << this->refractionCalc << std::endl;

	Vector3D<float> res3 = this->originalRay * this->indRefraction;
	float res4 = this->indRefraction * this->reflexionCalc - this->refractionCalc;
	Vector3D<float> res5 = this->normal * res4; 

	this->refractionRay = res3 + res5; 

	std::cout << "RefractionRay = " << this->refractionRay << std::endl;

}

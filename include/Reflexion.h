#ifndef __REFLEXION_DECLARATION__
#define __REFLEXION_DECLARATION__

#include "Vector.h"

class Reflexion
{
public:

	Reflexion();
	Reflexion(Reflexion const&) = delete;
	~Reflexion();

	auto	operator = (Reflexion const&) = delete;
	
	auto	init()	->	void;

	auto	dot_product(Vector3D<float> vec1, Vector3D<float> vec2)	->	float;
 
	auto	calculateReflexion()	->	void;
	auto	calculateRefraction()	->	void;

private:

	float			oriMedium;
	float			newMedium;
	float			indRefraction;
	float 			reflexionCalc;
	float 			refractionCalc;
	Vector3D<float>	originalRay;
	Vector3D<float> reflexionRay;
	Vector3D<float> refractionRay;
	Vector3D<float> normal;
	
	
};

#endif

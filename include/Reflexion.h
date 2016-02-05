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

private:

	Vector3D<float>	outputDir;
	Vector3D<float> inputDir;
	Vector3D<float> normal;
	
	
};

#endif

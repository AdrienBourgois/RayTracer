#ifndef __CAMERA_DECLARATION__
#define __CAMERA_DECLARATION__

#include "Vector.h"

class Camera
{
public:
	Camera() {;this->init;}
	~Camera();

private:
	Vector3D<float> position;
};

#endif

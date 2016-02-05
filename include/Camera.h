#ifndef __CAMERA_DECLARATION__
#define __CAMERA_DECLARATION__

#include "Vector.h"

class Camera
{
public:
	Camera();
	~Camera();

private:
	Vector3D<float> position;
};

#endif

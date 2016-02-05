#ifndef __RAY_DECLARATION__
#define __RAY_DECLARATION__

class Ray
{
public:
	Ray();
	~Ray();


private:
	Vector3D<float> start_posi;
	Vector3D<float> dir;
	float dist_max = 100.0f;
};

#endif

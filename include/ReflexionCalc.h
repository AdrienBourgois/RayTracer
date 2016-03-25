#ifndef __REFLEXIONCALC_DECLARATION__
#define __REFLEXIONCALC_DECLARATION__

#include <vector>

#include "GeometryBuffer.h"
#include "CollisionCalc.h"

auto ReflectRay(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Ray* ray, unsigned int rebound = 0) -> Vector3D<float>;

auto calculateReflexion(Vector3D<float> normal, Vector3D<float> ray_dir) -> Vector3D<float>;

auto calculateRefraction(Vector3D<float> normal, Vector3D<float> ray_dir) -> Vector3D<float>;
#endif

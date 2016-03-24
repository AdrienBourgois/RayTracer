#ifndef __REFLEXIONCALC_DECLARATION__
#define __REFLEXIONCALC_DECLARATION__

#include <vector>

#include "GeometryBuffer.h"
#include "CollisionCalc.h"

auto calculateReflexion(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Ray* ray, unsigned int rebound = 0) -> Vector3D<float>;
auto calcReflexion(GeometryBuffer* node, Ray* ray) -> Vector3D<float>;
auto calculateRefraction(GeometryBuffer* node, /*std::vector<GeometryBuffer*> node_list,*/ Ray* ray, float refraction_index) -> Vector3D<float>;

auto calculateRefraction(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Ray* ray, unsigned int rebound = 0) -> Vector3D<float>;
#endif

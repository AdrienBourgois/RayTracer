#ifndef __REFLEXIONCALC_DECLARATION__
#define __REFLEXIONCALC_DECLARATION__

#include <vector>

#include "GeometryBuffer.h"
#include "CollisionCalc.h"

auto calculateReflexion(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Vector3D<float> coll_point) -> Vector3D<float>;

#endif

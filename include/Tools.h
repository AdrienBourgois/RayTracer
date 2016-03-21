#ifndef __TOOLS_DECLARATION__
#define __TOOLS_DECLARATION__

#include <vector>

#include "CollisionCalc.h"
#include "GeometryBuffer.h"
#include "Ray.h"

auto FindNearestCollision(std::vector<GeometryBuffer*> node_list, Ray* ray, float& dist_min) -> GeometryBuffer*;

auto TriangleCast(GeometryBuffer* node) -> TriangleGeometryBuffer*;

auto SphereCast(GeometryBuffer* node) -> SphereGeometryBuffer*;

#endif

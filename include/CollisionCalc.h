#ifndef __COLLISIONCALC_DECLARATION__
#define __COLLISIONCALC_DECLARATION__

#include <vector>

#include "GeometryBuffer.h"
#include "Ray.h"

auto calculateCollision(GeometryBuffer* current_geometry, Ray* ray) -> float;
auto calculateSphereCollision(SphereGeometryBuffer* current_geometry, Ray* ray) -> float;
auto calculateModelCollision(TriangleGeometryBuffer* current_geometry, Ray* ray) -> float;

auto calculateCollisionPoint(float distance, Ray* ray) -> void;

auto isNodeBeforeLightSource(GeometryBuffer* current_node, std::vector<GeometryBuffer*> node_list, GeometryBuffer* light, Vector3D<float> coll_point) -> bool;

auto isCollisionWithNode(GeometryBuffer* current_node, std::vector<GeometryBuffer*> node_list, Ray* ray) -> GeometryBuffer*;

#endif

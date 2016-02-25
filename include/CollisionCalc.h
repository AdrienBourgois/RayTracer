#include "GeometryBuffer.h"
#include "Ray.h"

auto calculateCollision(SphereGeometryBuffer* current_geometry, Ray* ray) -> bool;

auto calculateCollisionPoint(float distance, Ray* ray) -> void;

#include "GeometryBuffer.h"
#include "Ray.h"

auto calculateCollision(SphereGeometryBuffer* current_geometry, Ray* ray) -> float;

auto calculateCollisionPoint(float distance, Ray* ray) -> void;

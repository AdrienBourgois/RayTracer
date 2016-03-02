#include "GeometryBuffer.h"
#include "Ray.h"

auto calculateCollision(GeometryBuffer* current_geometry, Ray* ray) -> float;
auto calculateSphereCollision(SphereGeometryBuffer* current_geometry, Ray* ray) -> float;
auto calculateTriangleCollision(TriangleGeometryBuffer* current_geometry, Ray* ray) -> float;
auto calculateModelCollision(TriangleGeometryBuffer* current_geometry, Ray* ray) -> float;

auto calculateCollisionPoint(float distance, Ray* ray) -> void;

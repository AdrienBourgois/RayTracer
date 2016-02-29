#include "Vector.h"
#include "GeometryBuffer.h"
#include "MaterialBuffer.h"
#include "Ray.h"

auto calculateAmbiantLight(GeometryBuffer* node) -> Vector3D<float>;
auto calculateDiffuseLight(GeometryBuffer* node, std::vector<GeometryBuffer*> light, Vector3D<float> coll_point) -> Vector3D<float>;
auto calculateSpecularLight(GeometryBuffer* node, std::vector<GeometryBuffer*> light, Ray* ray) -> Vector3D<float>;

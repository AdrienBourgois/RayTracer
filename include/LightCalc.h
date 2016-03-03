#ifndef __LIGHTCALC_DECLARATION__
#define __LIGHTCALC_DECLARATION__

#include <vector>

#include "Vector.h"
#include "GeometryBuffer.h"
#include "MaterialBuffer.h"
#include "Ray.h"

auto calculateAmbiantLight(GeometryBuffer* node) -> Vector3D<float>;

auto calculateDiffuseLight(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, std::vector<GeometryBuffer*> light, Ray* ray) -> Vector3D<float>;

auto calculateSpecularLight(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, std::vector<GeometryBuffer*> light, Ray* ray) -> Vector3D<float>;

#endif

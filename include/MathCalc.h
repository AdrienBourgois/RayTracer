#include <vector>

#include "Vector.h"

auto FindCameraRayDestinationPoint(Vector2D<float> render_size, float idx_x, float idx_y) -> Vector3D<float>;

auto NormalizeRenderSpace(Vector2D<float> render_size, float idx_x, float idx_y) -> Vector2D<float>;

auto CalculateU(Vector3D<float> a, Vector3D<float> b,Vector3D<float> c, Vector3D<float> ray_dir, Vector3D<float> ray_origin) -> float;

auto CalculateV(Vector3D<float> a, Vector3D<float> b,Vector3D<float> c, Vector3D<float> ray_dir, Vector3D<float> ray_origin) -> float;

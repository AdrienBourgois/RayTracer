#include <vector>

#include "Vector.h"

auto FindCameraRayDestinationPoint(Vector2D<float> render_size, float idx_x, float idx_y) -> Vector3D<float>;

auto NormalizeRenderSpace(Vector2D<float> render_size, float idx_x, float idx_y) -> Vector2D<float>;

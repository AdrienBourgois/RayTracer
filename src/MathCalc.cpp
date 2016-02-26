#include "MathCalc.h"

auto FindCameraRayDestinationPoint(Vector2D<float> render_size, float idx_x, float idx_y) -> Vector3D<float>
{
	Vector2D<float> NDC = NormalizeRenderSpace(render_size, idx_x, idx_y);

	Vector3D<float> dest_point;
	
	dest_point.x = ((2.f * NDC.x) - 1.f) *  (render_size.x / render_size.y);
	dest_point.y = (1.f - (2.f * NDC.y)); // * (render_size.y/render_size.x);

	return dest_point;
}

auto NormalizeRenderSpace(Vector2D<float> render_size, float idx_x, float idx_y) -> Vector2D<float>
{
	Vector2D<float> NDC;
	
	NDC.x = (idx_x + 0.5f) / render_size.x;
	NDC.y = (idx_y + 0.5f) / render_size.y;
	
	return NDC;
}

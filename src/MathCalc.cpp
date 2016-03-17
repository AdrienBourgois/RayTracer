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

auto CalculateU(Vector3D<float> a, Vector3D<float> b,Vector3D<float> c, Vector3D<float> ray_dir, Vector3D<float> ray_origin) -> float
{
	Vector3D<float> h = (c-a) * ray_dir;
	float _a = h.dot(b-a);
	
	if (_a > -0.00001f && _a < 0.00001f)
		return -1.f;

	float f = 1.f/_a;
        Vector3D<float> s = (ray_origin - a);
        return f * s.dot(h);
}

auto CalculateV(Vector3D<float> a, Vector3D<float> b,Vector3D<float> c, Vector3D<float> ray_dir, Vector3D<float> ray_origin) -> float
{
	Vector3D<float> h = ray_dir * (c - a);
        float _a = h.dot(b - a);
	float f = 1.f / _a;

	if (_a > -0.00001f && _a < 0.00001f)
		return -1.f;
	
	Vector3D<float> s = ray_origin - a;
	Vector3D<float> q = s * (b - a);
	return f * ray_dir.dot(q);
}


#ifndef __RAYTRACER_DECLARATION__
#define __RAYTRACER_DECLARATION__

#include <memory>

#include "Vector.h"
#include "RenderBuffer.h"
#include "Camera.h"

class RenderBuffer;
struct Camera;

class Raytracer final
{
	public:
		Raytracer();
		Raytracer(Raytracer const&) = delete;
		~Raytracer();

		auto init(Vector2D<float> screen_res) -> void;
		auto render() -> void;
		auto genGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list, bool light) -> void;
		auto genMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx) -> void;
		auto close() -> void;

	private:
	
		std::unique_ptr<RenderBuffer> render_buffer;
		std::unique_ptr<Camera> camera;

		std::vector<GeometryBuffer*> geometry_list;

		Vector2D<float> render_size;
};

#endif

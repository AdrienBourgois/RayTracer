#ifndef __RAYTRACER_DECLARATION__
#define __RAYTRACER_DECLARATION__

#include <memory>

#include "Vector.h"
#include "RenderBuffer.h"
#include "Camera.h"
#include "Enum.h"

class RenderBuffer;
struct Camera;
struct GeometryBuffer;
struct Ray;

class Raytracer final
{
	public:
		Raytracer();
		Raytracer(Raytracer const&) = delete;
		~Raytracer();

		auto init(Vector2D<float> screen_res) -> void;
		auto render() -> void;
		auto genGeometryBuffer(Vector3D<float> pos, float rad, std::vector<float> vert_list, EGeometry_type type_geometry) -> void;
		auto genMaterialBuffer(Vector3D<float> color_node, float reflct_idx, float refrct_idx, bool light) -> void;

		template <typename T>
		auto getGeometryPointer(GeometryBuffer* geometry_pointer) -> T*;

		auto getRenderBuffer() -> RenderBuffer* { return this->render_buffer.get(); }

		auto close() -> void;

	private:
	
		std::unique_ptr<RenderBuffer> 	render_buffer;
		std::unique_ptr<Camera> 		camera;

		std::vector<GeometryBuffer*> 	geometry_list;

		Vector2D<float> 				render_size;
		
		Ray* 							camera_ray;
};

#endif

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

	//	auto operator=(Raytracer const&) -> Raytracer = delete;
		
		auto init(Vector2D<float> screen_res) -> void;
		auto render() -> void;
		auto close() -> void;
	private:
	
		std::unique_ptr<RenderBuffer> render_buffer;
		std::unique_ptr<Camera> camera;

		Vector2D<float> render_size;
};

#endif

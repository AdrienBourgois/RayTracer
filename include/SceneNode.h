#ifndef __SCENENODE_DECLARATION__
#define __SCENENODE_DECLARATION__

#include <SDL2/SDL.h>
#include <vector>

#include "Raytracer.h"
#include "Vector.h"
#include "Enum.h"

class SceneNode
{
	public:
		SceneNode(Raytracer* raytrace);
		~SceneNode() {raytracer = nullptr;};

		auto init(Vector3D<float> pos, Vector3D<float> color, bool light, float rad, EGeometry_type type) -> void;
		auto draw() -> void;
		
		auto setPosition(Vector3D<float> pos) -> void;
		auto setColor(Vector3D<float> col) -> void { this->color = col; }
		auto setGeometryBufferId(unsigned int id) -> void { this->geometry_buffer_id = id; }

		auto getPosition() -> Vector3D<float> { return this->position; }
		auto getColor() -> Vector3D<float> { return this->color; }
		auto getVerticeList() -> std::vector<float> { return this-> vertice; }
		auto getIsLight() -> bool { return this->is_light; }
		auto getRadius() -> float {return this->radius; }
	private:
		
		Vector3D<float> position;
		Vector3D<float> color;
		
		std::vector<float> vertice;

		unsigned int geometry_buffer_id;

		float reflection_idx;
		float refraction_idx;
		float radius;

		bool is_light;

		Raytracer*		raytracer;
};

#endif

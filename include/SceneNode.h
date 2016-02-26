#ifndef __SCENENODE_DECLARATION__
#define __SCENENODE_DECLARATION__

#include <SDL2/SDL.h>
#include <vector>

#include "Vector.h"
#include "Enum.h"

class SceneNode
{
	public:
		SceneNode();
		~SceneNode() = default;

		auto init(Vector3D<float> pos, Vector3D<float> color, bool light, float rad, EGeometry_type type) -> void;
		
		auto setPosition(Vector3D<float> pos) -> void { this->position = pos; }
		auto setColor(Vector3D<float> col) -> void { this->color = col; }

		auto getPosition() -> Vector3D<float> { return this->position; }
		auto getColor() -> Vector3D<float> { return this->color; }
		auto getVerticeList() -> std::vector<float> { return this-> vertice; }
		auto getIsLight() -> bool { return this->is_light; }
		auto getRadius() -> float {return this->radius; }
	private:
		
		Vector3D<float> position;
		Vector3D<float> color;
		
		std::vector<float> vertice;

		float reflection_idx;
		float radius;

		bool is_light;
};

#endif

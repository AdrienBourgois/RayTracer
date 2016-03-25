#ifndef __DEVICE_DECLARATION__
#define __DEVICE_DECLARATION__

#include <vector>
#include <memory>
#include "Vector.h"
#include "Enum.h"

class Driver;
class Raytracer;
class SceneNode;

class Device final
{
    public:
        Device();
        Device(Device const&) = delete;
        Device(Device&&) = delete;
        ~Device();

        auto operator=(Device const&) -> Device& = delete;
        auto operator=(Device&&) -> Device& = delete;
    
        auto init() -> void;
        auto run() -> void;
	auto createSceneNode(Vector3D<float> pos, Vector3D<float> col, bool light, float rad, EGeometry_type type) -> void;
        auto quit() -> void;
        auto close() -> void;

        auto getDriver() const -> Driver const* {return driver.get(); }
	auto setLightList() -> void;
	auto getLightList() -> std::vector<SceneNode*> { return this->light_list; }
	auto getObjectList() -> std::vector<SceneNode*> { return this->object_list; }

    private:
        std::unique_ptr<Driver>		driver;
	std::unique_ptr<Raytracer>	raytracer;
	std::vector<SceneNode*>		node_list;		
		
        Vector2D<float>			screen_size;
		
	bool				running;
	std::vector<SceneNode*>		light_list;
	std::vector<SceneNode*>		object_list;
};

#endif


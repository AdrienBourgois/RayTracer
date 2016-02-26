#ifndef __DEVICE_DECLARATION__
#define __DEVICE_DECLARATION__

#include <vector>
#include <memory>
#include "Vector.h"

class Driver;
class Raytracer;
class SceneNode;

class Device final
{
    public:
        Device();
        Device(Device const&) = delete;
        ~Device();

        auto operator=(Device const&) -> Device& = delete;
    
        auto init() -> void;
        auto run() -> void;
		auto createSceneNode(Vector3D<float> pos, Vector3D<float> col, bool light, float rad) -> void;
        auto quit() -> void;
        auto close() -> void;

        auto getDriver() const -> Driver const*     {return driver.get(); }

    private:
        std::unique_ptr<Driver>     driver;
		std::unique_ptr<Raytracer>  raytracer;
		std::vector<SceneNode*>			node_list;		

        Vector2D<float>             screen_size;
		
        bool                        running;
};

#endif


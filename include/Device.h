#ifndef __DEVICE_DECLARATION__
#define __DEVICE_DECLARATION__

#include <memory>
#include <vector>

#include "Vector.h"
#include "Ray.h"

class Driver;
class RenderBuffer;
class Camera;
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
        auto quit() -> void;
        auto close() -> void;
        auto convert(Vector2D<int> vec) -> Vector2D<float>;

        auto getDriver() const -> Driver const*     {return driver.get(); }
		auto getLight() -> std::vector<SceneNode*> {return this->ray->getLightList();}

    private:
        std::unique_ptr<Driver>     driver;
        std::unique_ptr<RenderBuffer> render_buffer;
        std::unique_ptr<Camera>     camera;

        Vector2D<float>             screen_size;
        Ray*                        ray;

        std::vector<SceneNode*>     node_list;
        bool                        running;
        bool                        collision_result;
};

#endif

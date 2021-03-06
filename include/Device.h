#ifndef __DEVICE_DECLARATION__
#define __DEVICE_DECLARATION__

#include <memory>
#include "Vector.h"

class Driver;
class RenderBuffer;
class Camera;
class Ray;
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

    private:
        std::unique_ptr<Driver>     driver;
        std::unique_ptr<RenderBuffer> render_buffer;
        std::unique_ptr<Camera>     camera;

        Vector2D<int>               screen_size;
        Vector2D<float>             f_screen_size;
        Ray*                        ray;

        SceneNode*                  node_test;
        
        bool                        running;
        bool                        collision_result;
};

#endif

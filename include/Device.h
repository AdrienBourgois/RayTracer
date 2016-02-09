#ifndef __DEVICE_DECLARATION__
#define __DEVICE_DECLARATION__

#include <memory>
#include "Vector.h"

class Driver;
class RenderBuffer;
class Camera;
class Ray;

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

        auto getDriver() const -> Driver const*     {return driver.get(); }

    private:
        std::unique_ptr<Driver>     driver;
        std::unique_ptr<RenderBuffer> render_buffer;
        std::unique_ptr<Camera>     camera;

        Vector2D<int>             screen_size;

        Ray*                        ray;
        
        bool                        running;
};

#endif

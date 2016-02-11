#include <iostream>

#include "Device.h"
#include "Driver.h"
#include "RenderBuffer.h"
#include "Camera.h"
#include "Log.h"

#include "SceneNode.h"
#include "Ray.h"
//#include "Collision.h"

Device::Device()
{
    Log* log = Log::getInstance();
    log->info("Device creation...");

    this->collision_result = false;
    this->driver.reset(new Driver);
    this->render_buffer.reset(new RenderBuffer);
    this->camera.reset(new Camera);
    this->screen_size = Vector2D<int>(640.f, 480.f);
    this->f_screen_size = this->convert(this->screen_size);
    this->running = true;
    this->ray = nullptr;
    log->info("Device created.");
}

Device::~Device()
{
    Log* log = Log::getInstance();
    log->info("Device destruction...");
    this->driver = nullptr;
    this->running = false;
    log->info("Device destructed.");
}

auto Device::init() -> void
{
    Log* log = Log::getInstance();
    log->info("Device initialization...");
    this->driver->init(this->screen_size);
    this->camera->init(this->screen_size, this->render_buffer.get());
    log->info("Device initialized.");

	this->node_test = new SceneNode(ModelType::SPHERE);
	node_test->setPosition(Vector3D<float>(0.f, 0.f, -5.f)); 

    this->ray = new Ray(this->camera->getPosition(), this->convert(this->screen_size), this->render_buffer.get(), node_test, this->driver.get());
}

auto Device::run() -> void
{
    Log* log = Log::getInstance();
    log->info("Device running...");
    while(running)
    {
        this->ray->run();
        this->driver->changePixelColor(255, 0, 0, (this->render_buffer->getScreenCoordList()));
        driver->render();
    }
}

auto Device::quit() -> void
{
    this->running = false;
}

auto Device::close() -> void
{
    Log* log = Log::getInstance();
    log->info("Device closing...");
    this->driver->close();
    log->info("Device closed.");
}

auto Device::convert(Vector2D<int> vec) -> Vector2D<float>
{
    Vector2D<float> res;

    res.x = float(vec.x);
    res.y = float(vec.y);

    return res;
}

#include <iostream>

#include "Device.h"
#include "Driver.h"
#include "RenderBuffer.h"
#include "Camera.h"
#include "Log.h"

#include "SceneNode.h"
#include "Ray.h"
#include "Event.h"
//#include "Collision.h"

Device::Device()
{
    Log* log = Log::getInstance();
    log->info("Device creation...");

    this->collision_result = false;
    this->driver.reset(new Driver);
    this->render_buffer.reset(new RenderBuffer);
    this->camera.reset(new Camera);
    this->screen_size = Vector2D<float>(640.f, 480.f);
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
    this->camera = nullptr;
    this->render_buffer = nullptr;
    this->ray = nullptr;
    this->node_test = nullptr;

    log->info("Device destructed.");
}

auto Device::init() -> void
{
    Log* log = Log::getInstance();
    log->info("Device initialization...");
    this->driver->init(this->screen_size);
    this->camera->init(this->screen_size, this->render_buffer.get());
    log->info("Device initialized.");

	this->node_test = new SceneNode(ModelType::SPHERE, false);
	node_test->setPosition(Vector3D<float>(0.f, 0.f, -7.f));

    this->node_test2 = new SceneNode(ModelType::SPHERE, true);
    node_test2->setPosition(Vector3D<float>(0.f, 3.f, -2.f));

    this->node_list.push_back(node_test);
    this->node_list.push_back(node_test2);

    this->ray = new Ray(this->camera->getPosition(), this->screen_size,  this->render_buffer.get(), this->node_list, false);
}

auto Device::run() -> void
{
    Log* log = Log::getInstance();
    log->info("Device running...");
    while(running)
    {
        this->ray->run();
        this->driver->changePixelColor(this->render_buffer->getColorList(), this->render_buffer->getScreenCoordList());
        this->render_buffer->clearBuffer();

        driver->render();
	Event::eventListener(this);
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
    this->camera->close();
    this->ray->close();
    delete this->ray;
    delete this->node_test;
    
    log->info("Device closed.");
}

auto Device::convert(Vector2D<int> vec) -> Vector2D<float>
{
    Vector2D<float> res;

    res.x = float(vec.x);
    res.y = float(vec.y);

    return res;
}

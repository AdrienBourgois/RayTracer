#include <iostream>

#include "Device.h"
#include "Driver.h"
#include "Log.h"
#include "Event.h"
#include "Raytracer.h"
#include "SceneNode.h"

Device::Device()
{
    Log* log = Log::getInstance();
    log->info("Device creation...");

    this->driver.reset(new Driver);
	this->raytracer.reset(new Raytracer);
    this->screen_size = Vector2D<float>(640.f, 480.f);
    this->running = true;

    log->info("Device created.");
}

Device::~Device()
{
    Log* log = Log::getInstance();
    log->info("Device destruction...");
    this->driver = nullptr;
	this->raytracer = nullptr;
    this->running = false;
    log->info("Device destructed.");
}

auto Device::init() -> void
{
    Log* log = Log::getInstance();
    log->info("Device initialization...");
    this->driver->init(this->screen_size, this->raytracer.get());
	this->raytracer->init(this->screen_size);

	this->createSceneNode(Vector3D<float> (1.f, 0.f, -1.f), Vector3D<float> (255.f, 0.f, 0.f), false, 1.f);

	this->createSceneNode(Vector3D<float> (0.f, 1.f, -1.f), Vector3D<float> (255.f, 255.f, 0.f), false, 1.f);

	this->createSceneNode(Vector3D<float> (-1.f, 0.f, -1.f), Vector3D<float> (0.f, 255.f, 0.f), false, 1.f);

	this->createSceneNode(Vector3D<float> (0.f, -1.f, -1.f), Vector3D<float> (255.f, 255.f, 255.f), false, 1.f);

   // this->driver->changePixelColor(255, 255, 255, 120, 0);
}

auto Device::run() -> void
{
    Log* log = Log::getInstance();
    log->info("Device running...");
    while(running)
    {
		this->raytracer->render();
        driver->render();
        Event::eventListener(this);
    }
}

auto Device::createSceneNode(Vector3D<float> pos, Vector3D<float> col, bool light, float rad) -> void
{
	SceneNode* scene_node = new SceneNode();
	scene_node->init(pos, col, light, rad);

	this->node_list.push_back(scene_node);

	this->raytracer->genGeometryBuffer(pos, rad, scene_node->getVerticeList(), EGeometry_type::SPHERE);
	this->raytracer->genMaterialBuffer(col, 100.f, 0.f, false);
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
	this->raytracer->close();
    log->info("Device closed.");
}


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
	this->light_list.clear();
	this->object_list.clear();


    log->info("Device destructed.");
}

auto Device::init() -> void
{
    Log* log = Log::getInstance();
    log->info("Device initialization...");
    this->driver->init(this->screen_size, this->raytracer.get());
	this->raytracer->init(this->screen_size);

//	this->createSceneNode(Vector3D<float> (0.f, 0.f, -2.f), Vector3D<float> (255.f, 0.f, 0.f), false, 1.f, EGeometry_type::MODEL);
//	this->createSceneNode(Vector3D<float> (-3.f, 0.f, 0.f), Vector3D<float> (255.f, 255.f, 255.f), true, 0.01f, EGeometry_type::SPHERE);

	this->createSceneNode(Vector3D<float> (0.f, -1.f, -2.f), Vector3D<float> (255.f, 0.f, 0.f), false, 1.f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (-1.75f, 0.f, -2.f), Vector3D<float> (0.f, 255.f, 0.f), false, 1.f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (1.75f, 0.f, -2.f), Vector3D<float> (0.f, 0.f, 255.f), false, 1.f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (-5.f, -2.f, -4.f), Vector3D<float> (0.f, 255.f, 255.f),false, 1.f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (2.75f, 3.5f, -4.f), Vector3D<float> (255.f, 0.f, 255.f),false, 1.f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (-1.f, 2.f, -6.f), Vector3D<float> (55.f, 55.f, 55.f), false, 1.f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (-8.f, 4.f, -6.f), Vector3D<float> (55.f, 55.f, 0.f), false, 1.f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (5.f, -3.f, -6.f), Vector3D<float> (0.f, 55.f, 55.f), false, 1.f, EGeometry_type::SPHERE);

	this->createSceneNode(Vector3D<float> (-3.f, 1.f, -4.f), Vector3D<float> (255.f, 255.f, 255.f), true, 0.01f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (3.f, -3.f, 2.f), Vector3D<float> (255.f, 0.f, 0.f), true, 0.01f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (0.f, 0.f, 2.f), Vector3D<float> (0.f, 0.f, 255.f), true, 0.01f, EGeometry_type::SPHERE);
	this->createSceneNode(Vector3D<float> (4.f, 8.f, -8.f), Vector3D<float> (0.f, 255.f, 0.f), true, 0.01f, EGeometry_type::SPHERE);


	this->setLightList();
}

auto Device::run() -> void
{
    Log* log = Log::getInstance();
    log->info("Device running...");
	SceneNode* current_node = nullptr;
    while(running)
    {
		for(unsigned int idx = 0; idx < node_list.size(); ++idx)
		{
			current_node = node_list[idx];
			current_node->draw();
		}	
		this->raytracer->render();
        driver->render();
		Event::eventListener(this);
    }
}

auto Device::createSceneNode(Vector3D<float> pos, Vector3D<float> col, bool light, float rad, EGeometry_type type) -> void
{
	SceneNode* scene_node = new SceneNode(this->raytracer.get());
	scene_node->init(pos, col, light, rad, type);

	this->node_list.push_back(scene_node);

	unsigned int id = this->raytracer->genGeometryBufferId();
	this->raytracer->genGeometryBuffer(pos, rad, scene_node->getVerticeList(), type, id);
	this->raytracer->genMaterialBuffer(col, 100.f, 1.5f, light);
	
	scene_node->setGeometryBufferId(id);
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

	for (unsigned int i = 0; i < this->node_list.size(); ++i)
	{
		delete this->node_list[i];
	}
    log->info("Device closed.");
}

auto Device::setLightList() -> void
{
	SceneNode* current_node = nullptr;

	for(unsigned int idx = 0; idx < this->node_list.size(); ++idx)
	{
		current_node = node_list[idx];
		if (current_node->getIsLight())
			this->light_list.push_back(current_node);
		else
			this->object_list.push_back(current_node);
	}
}


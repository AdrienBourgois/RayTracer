#include <iostream>

#include "Device.h"
#include "Driver.h"
#include "Camera.h"
#include "Log.h"

//Log* log = Log::getInstance();

#include "SceneNode.h"
#include "Ray.h"
#include "Collision.h"

Device::Device()
{
    Log* log = Log::getInstance();
    log->info("Device creation...");

    this->driver.reset(new Driver);
    this->camera.reset(new Camera);
    this->screen_size = Vector2D<int>(640.f, 480.f);
    this->running = true;

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

    this->camera->init(this->screen_size);
    log->info("Device initialized.");

//------------------- TEST ------------------------------------------------------------//
	SceneNode node_test = SceneNode(ModelType::SPHERE);
	node_test.setPosition(Vector3D<float>(0.f, 0.f, -15.f)); 

	SceneNode plan_test = SceneNode(ModelType::TRIANGLE);
	plan_test.setPosition(Vector3D<float>(-2.f, -2.f, -1.f));
	
	Ray ray = Ray(Vector3D<float>(0.f, 0.f, 10.f), Vector3D<float>(0.f, 0.f, -1.f));
	Collision collision = Collision();

	Vector2D<unsigned int> resolution = Vector2D<unsigned int>(640, 480);
//--------------------- AFFICHAGE ------------------------------------------------------//	
	float rx = -1;
	float ry = 1;
	for (unsigned int i = 0; i < resolution.y; ++i)
	{
		ry = ry - (1.0f/((float)resolution.y/2.f));
		for (unsigned int j = 0; j < resolution.y; ++j)
		{
			rx = rx + (1.0f/((float)resolution.x/2.f));

			ray.setRayDirection(Vector3D<float>(rx, ry, -1.f));
//			bool result = collision.rayCircleCollision(ray, node_test);
			bool result2 =collision.rayTriangleCollision(ray, plan_test);

//			if (result)
//				this->driver->changePixelColor(255, 255, 255, j, i);
			if (result2)
				this->driver->changePixelColor(250, 250, 255, j, i);
		}
		rx = -1;
	}
//--------------------- END AFFICHAGE ------------------------------------------------------//	
//------------------- END TEST ------------------------------------------------------------//
}

auto Device::run() -> void
{
    Log* log = Log::getInstance();
    log->info("Device running...");
    while(running)
    {
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

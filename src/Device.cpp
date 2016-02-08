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

	SceneNode node_test = SceneNode(ModelType::SPHERE);
	node_test.setPosition(Vector3D<float>(-3.f, -5.f, -15.f)); 
	
	Ray ray = Ray(Vector3D<float>(0.f, 0.f, 5.f), Vector3D<float>(0.f, 0.f, -1.f));
	Collision collision = Collision();

	SceneNode plan_test = SceneNode(ModelType::PLANE);
	plan_test.setPosition(Vector3D<float>(0.f, -4.f, -5.f));



/*	for (float i = 2; i > 0; i -= 1.0f/240.f)
	{
		for (float j = 0; j < 2; j += 1.0f/320.f)
*/
	float rx = -1;
	float ry = 1;
	for (unsigned int i = 0; i < 480; ++i)
	{
		ry = ry - (1.0f/240.f);
		for (unsigned int j = 0; j < 640; ++j)
		{
			rx = rx + (1.0f/320.f);

			ray.setRayDirection(Vector3D<float>(rx, ry, -1.f));
			bool result = collision.rayCircleCollision(ray, node_test);
			bool result2 = collision.rayPlaneCollision(ray, plan_test);
(void)result2;

			if (result)
				this->driver->changePixelColor(255, 255, 255, j, i);
//				this->driver->changePixelColor(255, 255, 255, x_count, y_count);
//			if (result2)
//				this->driver->changePixelColor(255, 0, 0, x_count, y_count);

		}
		rx = -1;
	}
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

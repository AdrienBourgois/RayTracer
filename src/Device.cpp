#include <iostream>

#include "Device.h"
#include "Driver.h"
#include "Log.h"
#include "Reflexion.h"

//Log* log = Log::getInstance();

Device::Device()
{
    Log* log = Log::getInstance();
    log->info("Device creation...");
    this->driver.reset(new Driver);
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
    log->info("Device initialized.");
	
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

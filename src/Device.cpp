#include <iostream>

#include "Device.h"
#include "Driver.h"
#include "RenderBuffer.h"
#include "Camera.h"
#include "Log.h"

//Log* log = Log::getInstance();

Device::Device()
{
    Log* log = Log::getInstance();
    log->info("Device creation...");

    this->driver.reset(new Driver);
    this->render_buffer.reset(new RenderBuffer);
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
    this->camera->init(this->screen_size, this->render_buffer.get());
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

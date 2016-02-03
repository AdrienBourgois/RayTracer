#include <iostream>

#include "Device.h"
#include "Driver.h"

Device::Device()
{
    this->driver.reset(new Driver);
    this->screen_size = Vector2D<int>(640.f, 480.f);
    this->running = true;
}

Device::~Device()
{
    this->driver = nullptr;
    this->running = false;
}

auto Device::init() -> void
{
    this->driver->init(this->screen_size);
}

auto Device::run() -> void
{
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
    this->driver->close();
}

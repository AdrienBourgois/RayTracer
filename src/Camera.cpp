#include "Camera.h"
#include "Ray.h"
#include "Log.h"

Camera::Camera()
{
    Log* log = Log::getInstance();
    log->info("Camera creation...");

    this->FOV = 0;
    this->lookAt = Vector3D<float> (0.f, 0.f, 0.f);
    
    log->info("Camera created.");
}

auto Camera::init(Vector2D<int> screen_res, RenderBuffer* rend_buffer) -> void
{
    Log* log = Log::getInstance();
    log->info("Camera initialization...");

    this->render_buffer = rend_buffer;

	this->position = Vector3D<float>(0.f, 0.f, 1.0f);
    this->viewDirection = this->lookAt - this->position;
    this->up = Vector3D<float> (0.f, 1.f, 0.f);
    this->screen_size.x = float (screen_res.x);
    this->screen_size.y = float (screen_res.y);
    this->u = viewDirection * up;
    this->v = u * viewDirection;

    log->info("Camera initilized.");
}

auto Camera::close() -> void
{
    this->render_buffer = nullptr;
}
